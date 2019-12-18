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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int fsize ; 
 scalar_t__ ftruncate (int,scalar_t__) ; 
 scalar_t__ offset ; 
 int /*<<< orphan*/  perror (char*) ; 
 int random () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ vflag ; 

__attribute__((used)) static void
do_trunc(int fd)
{
	off_t   roffset = 0;

	roffset = random() % fsize;
	if (ftruncate(fd, (offset + roffset))  < 0) {
		perror("truncate");
		exit(7);
	}

	if (vflag) {
		(void) fprintf(stderr,
		    "Truncated at offset %ld\n",
		    (offset + roffset));
	}
}