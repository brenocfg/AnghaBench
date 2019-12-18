#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long elm_idx; long* cstat; } ;
typedef  TYPE_1__ encioc_elm_status_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENCIOC_SETELMSTAT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 

int
main(int a, char **v)
{
	int fd;
	int i;
	encioc_elm_status_t obj;
	long cvt;
	char *x;

	if (a != 7) {
usage:
		fprintf(stderr,
		    "usage: %s device objectid stat0 stat1 stat2 stat3\n", *v);
		return (1);
	}
	fd = open(v[1], O_RDWR);
	if (fd < 0) {
		perror(v[1]);
		return (1);
	}
	x = v[2];
	cvt = strtol(v[2], &x, 0);
	if (x == v[2]) {
		goto usage;
	}
	obj.elm_idx = cvt;
	for (i = 0; i < 4; i++) {
		x = v[3 + i];
		cvt = strtol(v[3 + i],  &x, 0);
		if (x == v[3 + i]) {
			goto usage;
		}
		obj.cstat[i] = cvt;
	}
	if (ioctl(fd, ENCIOC_SETELMSTAT, (caddr_t) &obj) < 0) {
		perror("ENCIOC_SETELMSTAT");
	}
	(void) close(fd);
	return (0);
}