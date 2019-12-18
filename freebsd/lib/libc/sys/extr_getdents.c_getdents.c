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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  _getdirentries (int,char*,size_t,int /*<<< orphan*/ *) ; 

ssize_t
getdents(int fd, char *buf, size_t nbytes)
{
	/*
	 * _getdirentries knows how to call the right thing and
	 * return it in the new format. It assumes that the entire
	 * libc expecting the new format.
	 */

	return (_getdirentries(fd, buf, nbytes, NULL));
}