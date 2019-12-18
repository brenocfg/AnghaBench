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
typedef  scalar_t__ vptr ;
typedef  int /*<<< orphan*/  restore_list ;

/* Variables and functions */
 scalar_t__ _found ; 
 int /*<<< orphan*/  _found_a ; 
 int /*<<< orphan*/  _found_b ; 
 int /*<<< orphan*/  _needed_id ; 
 int /*<<< orphan*/  _prev_id ; 
 scalar_t__ restore_list_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void search_for_id (int *prev, vptr *_list_ptr) {
  if (_found > 0) {
    return;
  }
  restore_list *list = (restore_list *) *_list_ptr;

  _found = restore_list_del (list, _needed_id, &_found_a, &_found_b, _prev_id);
}