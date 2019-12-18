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
struct lev_search_delete_item {long long obj_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_SEARCH_DELETE_ITEM ; 
 struct lev_search_delete_item* alloc_log_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct lev_search_delete_item*) ; 
 int delete_item (long long) ; 
 int /*<<< orphan*/  fits (long long) ; 

int do_delete_item (long long item_id) {
  if (!fits (item_id)) { return 0; }
  struct lev_search_delete_item *ED = alloc_log_event (LEV_SEARCH_DELETE_ITEM, 12, 0);
  assert (ED);
  ED->obj_id = item_id;
  return delete_item (item_id);
}