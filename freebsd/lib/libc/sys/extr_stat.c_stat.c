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
struct stat {int dummy; } ;
struct freebsd11_stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 scalar_t__ INO64_FIRST ; 
 int /*<<< orphan*/  SYS_freebsd11_stat ; 
 scalar_t__ __getosreldate () ; 
 int /*<<< orphan*/  __stat11_to_stat (struct freebsd11_stat*,struct stat*) ; 
 int __sys_fstatat (int /*<<< orphan*/ ,char const*,struct stat*,int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,char const*,struct freebsd11_stat*) ; 

int
stat(const char *path, struct stat *sb)
{
	struct freebsd11_stat stat11;
	int rv;

	if (__getosreldate() >= INO64_FIRST)
		return (__sys_fstatat(AT_FDCWD, path, sb, 0));
	rv = syscall(SYS_freebsd11_stat, path, &stat11);
	if (rv == 0)
		__stat11_to_stat(&stat11, sb);
	return (rv);
}