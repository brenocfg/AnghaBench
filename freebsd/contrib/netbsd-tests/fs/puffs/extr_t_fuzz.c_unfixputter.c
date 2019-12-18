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
struct puffs_kargs {int /*<<< orphan*/  pa_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  rump_sys_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
unfixputter(struct puffs_kargs *kargs)
{

	rump_sys_close(kargs->pa_fd);
}