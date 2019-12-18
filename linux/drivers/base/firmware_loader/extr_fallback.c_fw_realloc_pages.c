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
struct fw_sysfs {int /*<<< orphan*/  fw_priv; } ;

/* Variables and functions */
 int PAGE_ALIGN (int) ; 
 int PAGE_SHIFT ; 
 int fw_grow_paged_buf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fw_load_abort (struct fw_sysfs*) ; 

__attribute__((used)) static int fw_realloc_pages(struct fw_sysfs *fw_sysfs, int min_size)
{
	int err;

	err = fw_grow_paged_buf(fw_sysfs->fw_priv,
				PAGE_ALIGN(min_size) >> PAGE_SHIFT);
	if (err)
		fw_load_abort(fw_sysfs);
	return err;
}