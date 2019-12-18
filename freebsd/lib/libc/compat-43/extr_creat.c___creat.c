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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 size_t INTERPOS_openat ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int,char const*,int) ; 

int
__creat(const char *path, mode_t mode)
{

	return (((int (*)(int, const char *, int, ...))
	    __libc_interposing[INTERPOS_openat])(AT_FDCWD, path, O_WRONLY |
	    O_CREAT | O_TRUNC, mode));
}