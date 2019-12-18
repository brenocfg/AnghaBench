#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {scalar_t__ type; size_t page_count; int /*<<< orphan*/  key; int /*<<< orphan*/ * pages; TYPE_2__* bridge; scalar_t__ is_bound; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* agp_destroy_page ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* agp_destroy_pages ) (struct agp_memory*) ;int /*<<< orphan*/  (* free_by_type ) (struct agp_memory*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_PAGE_DESTROY_FREE ; 
 int /*<<< orphan*/  AGP_PAGE_DESTROY_UNMAP ; 
 scalar_t__ AGP_USER_TYPES ; 
 int /*<<< orphan*/  agp_free_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_page_array (struct agp_memory*) ; 
 int /*<<< orphan*/  agp_generic_free_by_type (struct agp_memory*) ; 
 int /*<<< orphan*/  agp_unbind_memory (struct agp_memory*) ; 
 int /*<<< orphan*/  kfree (struct agp_memory*) ; 
 int /*<<< orphan*/  stub1 (struct agp_memory*) ; 
 int /*<<< orphan*/  stub2 (struct agp_memory*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void agp_free_memory(struct agp_memory *curr)
{
	size_t i;

	if (curr == NULL)
		return;

	if (curr->is_bound)
		agp_unbind_memory(curr);

	if (curr->type >= AGP_USER_TYPES) {
		agp_generic_free_by_type(curr);
		return;
	}

	if (curr->type != 0) {
		curr->bridge->driver->free_by_type(curr);
		return;
	}
	if (curr->page_count != 0) {
		if (curr->bridge->driver->agp_destroy_pages) {
			curr->bridge->driver->agp_destroy_pages(curr);
		} else {

			for (i = 0; i < curr->page_count; i++) {
				curr->bridge->driver->agp_destroy_page(
					curr->pages[i],
					AGP_PAGE_DESTROY_UNMAP);
			}
			for (i = 0; i < curr->page_count; i++) {
				curr->bridge->driver->agp_destroy_page(
					curr->pages[i],
					AGP_PAGE_DESTROY_FREE);
			}
		}
	}
	agp_free_key(curr->key);
	agp_free_page_array(curr);
	kfree(curr);
}