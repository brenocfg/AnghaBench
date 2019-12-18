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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct vm_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_map_min (struct vm_map const*) ; 

vm_offset_t
vm_map_min_KBI(const struct vm_map *map)
{

	return (vm_map_min(map));
}