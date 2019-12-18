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
struct devfs_dirent {int /*<<< orphan*/ * de_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  mac_devfs_label_free (int /*<<< orphan*/ *) ; 

void
mac_devfs_destroy(struct devfs_dirent *de)
{

	if (de->de_label != NULL) {
		mac_devfs_label_free(de->de_label);
		de->de_label = NULL;
	}
}