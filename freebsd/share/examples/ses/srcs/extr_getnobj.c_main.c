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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SESIOC_GETNOBJ ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,unsigned int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stdout ; 

int
main(int argc, char **argv)
{
	unsigned int nobj;
	int fd;

	while (*++argv != NULL) {
		char *name = *argv;
		fd = open(name, O_RDONLY);
		if (fd < 0) {
			perror(name);
			continue;
		}
		if (ioctl(fd, SESIOC_GETNOBJ, (caddr_t) &nobj) < 0) {
			perror("SESIOC_GETNOBJ");
		} else {
			fprintf(stdout, "%s: %d objects\n", name, nobj);
		}
		close (fd);
	}
	return (0);
}