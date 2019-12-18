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
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 scalar_t__ isolated_loader ; 
 int /*<<< orphan*/  isolated_loader_size ; 

__attribute__((used)) static void spufs_exit_isolated_loader(void)
{
	free_pages((unsigned long) isolated_loader,
			get_order(isolated_loader_size));
}