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
typedef  scalar_t__ u16 ;
struct vio_version {scalar_t__ major; } ;
struct vio_driver_state {int ver_table_entries; struct vio_version* ver_table; } ;

/* Variables and functions */

__attribute__((used)) static struct vio_version *find_by_major(struct vio_driver_state *vio,
					 u16 major)
{
	struct vio_version *ret = NULL;
	int i;

	for (i = 0; i < vio->ver_table_entries; i++) {
		struct vio_version *v = &vio->ver_table[i];
		if (v->major <= major) {
			ret = v;
			break;
		}
	}
	return ret;
}