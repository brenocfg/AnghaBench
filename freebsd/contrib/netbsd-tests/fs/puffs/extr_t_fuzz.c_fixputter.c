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
struct puffs_kargs {int pa_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fixputter(struct puffs_kargs *kargs)
{

	kargs->pa_fd = rump_sys_open("/dev/putter", O_RDWR);
	if (kargs->pa_fd == -1)
		atf_tc_fail_errno("open putter");
}