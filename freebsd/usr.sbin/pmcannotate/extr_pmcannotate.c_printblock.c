#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_int ;
struct entry {scalar_t__ en_nsamples; } ;
struct aggent {float ag_nsamples; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LNBUFF ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 struct entry* general_findent (uintptr_t) ; 
 scalar_t__ isasminline (char*) ; 
 int newfunction (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,void**) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
printblock(FILE *fp, struct aggent *agg)
{
	char buffer[LNBUFF];
	long lstart;
	struct entry *obj;
	u_int tnsamples;
	int done, nbytes, sentinel;
	void *ptr;

	/*
	 * We expect the first thing of the block is C code, so simply give
	 * up if asm line is found.
	 */
	lstart = ftell(fp);
	sentinel = 0;
	for (;;) {
		if (fgets(buffer, LNBUFF, fp) == NULL)
			return (0);
		if (isasminline(buffer) != 0)
			break;
		sentinel = 1;
		nbytes = newfunction(buffer);
		if (nbytes != 0) {
			if (fseek(fp, nbytes * -1, SEEK_CUR) == -1)
				return (-1);
			return (0);
		}
	}

	/*
	 * If the sentinel is not set, it means it did not match any
	 * "high half" for this code so simply give up.
	 * Operates the second-level aggregation.
	 */
	tnsamples = 0;
	do {
		if (sentinel == 0)
			return (-1);
		if (sscanf(buffer, " %p:", &ptr) != 1)
			return (-1);
		obj = general_findent((uintptr_t)ptr);
		if (obj != NULL)
			tnsamples += obj->en_nsamples;
	} while (fgets(buffer, LNBUFF, fp) != NULL && isasminline(buffer) != 0);

	/* Rewind to the start of the block in order to start the printout. */
	if (fseek(fp, lstart, SEEK_SET) == -1)
		return (-1);

	/* Again the high half of the block rappresenting the C part. */
	done = 0;
	while (fgets(buffer, LNBUFF, fp) != NULL && isasminline(buffer) == 0) {
		if (tnsamples == 0 || done != 0)
			printf("\t| %s", buffer);
		else {
			done = 1;
			printf("%.2f%%\t| %s",
			    (float)tnsamples * 100 / agg->ag_nsamples, buffer);
		}
	}

	/*
	 * Again the low half of the block rappresenting the asm
	 * translation part.
	 */
	for (;;) {
		if (fgets(buffer, LNBUFF, fp) == NULL)
			return (0);
		if (isasminline(buffer) == 0)
			break;
		nbytes = newfunction(buffer);
		if (nbytes != 0) {
			if (fseek(fp, nbytes * -1, SEEK_CUR) == -1)
				return (-1);
			return (0);
		}
	}
	if (fseek(fp, strlen(buffer) * -1, SEEK_CUR) == -1)
		return (-1);
	return (0);
}