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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int read (int,void*,int) ; 

int load_payload(char *fname, void *buf, int len)
{
	int fd;
	int rc;

	if ((fd = open(fname, O_RDONLY)) == -1)
		err(1, "open()");

	if ((rc = read(fd, buf, len)) == -1)
		err(1, "read()");

	close(fd);
	printf("Read %d bytes from %s\n", rc, fname);
	return rc;
}