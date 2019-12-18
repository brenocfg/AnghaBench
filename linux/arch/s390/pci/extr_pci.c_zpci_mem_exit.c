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
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zdev_fmb_cache ; 
 int /*<<< orphan*/  zpci_iomap_bitmap ; 
 int /*<<< orphan*/  zpci_iomap_start ; 

__attribute__((used)) static void zpci_mem_exit(void)
{
	kfree(zpci_iomap_bitmap);
	kfree(zpci_iomap_start);
	kmem_cache_destroy(zdev_fmb_cache);
}