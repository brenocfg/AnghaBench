#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sglist {int dummy; } ;
struct hv_sgl_node {struct sglist* sgl_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_sgl_list; int /*<<< orphan*/  in_use_sgl_list; } ;

/* Variables and functions */
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct hv_sgl_node* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hv_sgl_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct hv_sgl_node*,int /*<<< orphan*/ ) ; 
 TYPE_1__ g_hv_sgl_page_pool ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
storvsc_destroy_bounce_buffer(struct sglist *sgl)
{
	struct hv_sgl_node *sgl_node = NULL;
	if (LIST_EMPTY(&g_hv_sgl_page_pool.in_use_sgl_list)) {
		printf("storvsc error: not enough in use sgl\n");
		return;
	}
	sgl_node = LIST_FIRST(&g_hv_sgl_page_pool.in_use_sgl_list);
	LIST_REMOVE(sgl_node, link);
	sgl_node->sgl_data = sgl;
	LIST_INSERT_HEAD(&g_hv_sgl_page_pool.free_sgl_list, sgl_node, link);
}