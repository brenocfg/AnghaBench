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
struct memory_type_list {int /*<<< orphan*/  mtl_list; } ;
struct memory_type {int dummy; } ;

/* Variables and functions */
 struct memory_type* LIST_FIRST (int /*<<< orphan*/ *) ; 

struct memory_type *
memstat_mtl_first(struct memory_type_list *list)
{

	return (LIST_FIRST(&list->mtl_list));
}