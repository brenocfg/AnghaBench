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
struct memory_type_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _memstat_mtl_empty (struct memory_type_list*) ; 
 int /*<<< orphan*/  free (struct memory_type_list*) ; 

void
memstat_mtl_free(struct memory_type_list *list)
{

	_memstat_mtl_empty(list);
	free(list);
}