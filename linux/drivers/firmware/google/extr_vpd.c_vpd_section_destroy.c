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
struct vpd_section {int enabled; int /*<<< orphan*/  baseaddr; int /*<<< orphan*/  raw_name; int /*<<< orphan*/  bin_attr; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpd_kobj ; 
 int /*<<< orphan*/  vpd_section_attrib_destroy (struct vpd_section*) ; 

__attribute__((used)) static int vpd_section_destroy(struct vpd_section *sec)
{
	if (sec->enabled) {
		vpd_section_attrib_destroy(sec);
		kobject_put(sec->kobj);
		sysfs_remove_bin_file(vpd_kobj, &sec->bin_attr);
		kfree(sec->raw_name);
		memunmap(sec->baseaddr);
		sec->enabled = false;
	}

	return 0;
}