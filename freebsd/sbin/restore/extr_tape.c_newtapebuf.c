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

/* Variables and functions */
 int TP_BSIZE ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (long) ; 
 long ntrec ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * tapebuf ; 

void
newtapebuf(long size)
{
	static int tapebufsize = -1;

	ntrec = size;
	if (size <= tapebufsize)
		return;
	if (tapebuf != NULL)
		free(tapebuf - TP_BSIZE);
	tapebuf = malloc((size+1) * TP_BSIZE);
	if (tapebuf == NULL) {
		fprintf(stderr, "Cannot allocate space for tape buffer\n");
		done(1);
	}
	tapebuf += TP_BSIZE;
	tapebufsize = size;
}