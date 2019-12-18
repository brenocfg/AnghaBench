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
struct resource_map {int /*<<< orphan*/  r_vaddr; int /*<<< orphan*/  r_size; int /*<<< orphan*/  r_bushandle; int /*<<< orphan*/  r_bustag; } ;
struct resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_get_virtual (struct resource*) ; 

void
rman_get_mapping(struct resource *r, struct resource_map *map)
{

	map->r_bustag = rman_get_bustag(r);
	map->r_bushandle = rman_get_bushandle(r);
	map->r_size = rman_get_size(r);
	map->r_vaddr = rman_get_virtual(r);
}