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
 int /*<<< orphan*/  debugfs_create_file_unsafe (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeh_addr_cache_fops ; 
 int /*<<< orphan*/  powerpc_debugfs_root ; 

void eeh_cache_debugfs_init(void)
{
	debugfs_create_file_unsafe("eeh_address_cache", 0400,
			powerpc_debugfs_root, NULL,
			&eeh_addr_cache_fops);
}