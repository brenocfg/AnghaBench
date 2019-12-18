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
struct vop_access_args {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
autofs_access(struct vop_access_args *ap)
{

	/*
	 * Nothing to do here; the only kind of access control
	 * needed is in autofs_mkdir().
	 */

	return (0);
}