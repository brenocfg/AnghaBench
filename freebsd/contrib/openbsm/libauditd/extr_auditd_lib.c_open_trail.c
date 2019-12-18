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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDONLY ; 
 int S_IRGRP ; 
 int S_IRUSR ; 
 scalar_t__ auditctl (char*) ; 
 int /*<<< orphan*/  auditdist_link (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ fchmod (int,int) ; 
 scalar_t__ fchown (int,int,int /*<<< orphan*/ ) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int
open_trail(char *fname, gid_t gid, int *errorp)
{
	int fd;

	/* XXXPJD: What should we do if the file already exists? */
	fd = open(fname, O_RDONLY | O_CREAT, S_IRUSR);
	if (fd < 0)
		return (-1);
	if (fchown(fd, -1, gid) < 0 || fchmod(fd, S_IRUSR | S_IRGRP) < 0) {
		(void) close(fd);
		(void) unlink(fname);
		return (-1);
	}
	(void) close(fd);
	if (auditctl(fname) < 0) {
		*errorp = errno;
		(void) unlink(fname);
		return (-1);
	}
	(void) auditdist_link(fname);
	return (0);
}