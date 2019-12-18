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
struct entry {scalar_t__ en_nsamples; } ;
struct aggent {float ag_nsamples; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LNBUFF ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct entry* general_findent (uintptr_t) ; 
 int /*<<< orphan*/  isasminline (char*) ; 
 int newfunction (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sscanf (char*,char*,void**) ; 

__attribute__((used)) static void
general_printasm(FILE *fp, struct aggent *agg)
{
	char buffer[LNBUFF];
	struct entry *obj;
	int nbytes;
	void *ptr;

	while (fgets(buffer, LNBUFF, fp) != NULL) {
		if ((nbytes = newfunction(buffer)) != 0) {
			fseek(fp, nbytes * -1, SEEK_CUR);
			break;
		}
		if (!isasminline(buffer))
			continue;
		if (sscanf(buffer, " %p:", &ptr) != 1)
			continue;
		obj = general_findent((uintptr_t)ptr);
		if (obj == NULL)
			printf("\t| %s", buffer);
		else
			printf("%.2f%%\t| %s",
			    (float)obj->en_nsamples * 100 / agg->ag_nsamples,
			    buffer);
	}
}