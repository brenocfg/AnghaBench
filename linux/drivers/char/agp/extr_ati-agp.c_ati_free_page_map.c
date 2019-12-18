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
struct ati_page_map {scalar_t__ real; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  set_memory_wb (unsigned long,int) ; 
 int /*<<< orphan*/  unmap_page_from_agp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

__attribute__((used)) static void ati_free_page_map(struct ati_page_map *page_map)
{
	unmap_page_from_agp(virt_to_page(page_map->real));
	set_memory_wb((unsigned long)page_map->real, 1);
	free_page((unsigned long) page_map->real);
}