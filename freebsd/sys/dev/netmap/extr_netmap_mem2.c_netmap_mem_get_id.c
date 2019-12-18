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
struct netmap_mem_d {int /*<<< orphan*/  nm_id; } ;
typedef  int /*<<< orphan*/  nm_memid_t ;

/* Variables and functions */

nm_memid_t
netmap_mem_get_id(struct netmap_mem_d *nmd)
{
	return nmd->nm_id;
}