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
typedef  scalar_t__ vm_offset_t ;
struct acpi_user_mapping {scalar_t__ pa; scalar_t__ size; scalar_t__ va; } ;

/* Variables and functions */
 struct acpi_user_mapping* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct acpi_user_mapping*,int /*<<< orphan*/ ) ; 
 struct acpi_user_mapping* LIST_NEXT (struct acpi_user_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  acpi_mem_fd ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  link ; 
 struct acpi_user_mapping* malloc (int) ; 
 int /*<<< orphan*/  maplist ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

__attribute__((used)) static struct acpi_user_mapping *
acpi_user_find_mapping(vm_offset_t pa, size_t size)
{
	struct	acpi_user_mapping *map;

	/* First search for an existing mapping */
	for (map = LIST_FIRST(&maplist); map; map = LIST_NEXT(map, link)) {
		if (map->pa <= pa && map->size >= pa + size - map->pa)
			return (map);
	}

	/* Then create a new one */
	size = round_page(pa + size) - trunc_page(pa);
	pa = trunc_page(pa);
	map = malloc(sizeof(struct acpi_user_mapping));
	if (!map)
		errx(1, "out of memory");
	map->pa = pa;
	map->va = mmap(0, size, PROT_READ, MAP_SHARED, acpi_mem_fd, pa);
	map->size = size;
	if ((intptr_t) map->va == -1)
		err(1, "can't map address");
	LIST_INSERT_HEAD(&maplist, map, link);

	return (map);
}