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
typedef  int /*<<< orphan*/  uint64_t ;
struct mntarg {int dummy; } ;

/* Variables and functions */
 int kernel_mount (struct mntarg*,int /*<<< orphan*/ ) ; 

int
fdesc_cmount(struct mntarg *ma, void *data, uint64_t flags)
{

	return kernel_mount(ma, flags);
}