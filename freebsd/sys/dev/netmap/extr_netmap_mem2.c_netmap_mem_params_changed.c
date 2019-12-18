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
struct netmap_obj_params {scalar_t__ last_size; scalar_t__ size; scalar_t__ last_num; scalar_t__ num; } ;

/* Variables and functions */
 int NETMAP_POOLS_NR ; 

__attribute__((used)) static int
netmap_mem_params_changed(struct netmap_obj_params* p)
{
	int i, rv = 0;

	for (i = 0; i < NETMAP_POOLS_NR; i++) {
		if (p[i].last_size != p[i].size || p[i].last_num != p[i].num) {
			p[i].last_size = p[i].size;
			p[i].last_num = p[i].num;
			rv = 1;
		}
	}
	return rv;
}