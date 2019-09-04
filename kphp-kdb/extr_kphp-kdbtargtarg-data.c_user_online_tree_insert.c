#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  last_visited; } ;
typedef  TYPE_1__ user_t ;
typedef  int /*<<< orphan*/  olist_t ;

/* Variables and functions */
 int /*<<< orphan*/ * OHead ; 
 int OLIST_COUNT ; 
 scalar_t__ is_valid_online_stamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocntT ; 
 int online_convert_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  online_list_add_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_to_olist (TYPE_1__*) ; 

void user_online_tree_insert (user_t *U) {
  if (is_valid_online_stamp (U->last_visited)) {
    int p = online_convert_time (U->last_visited);
    online_list_add_after ((olist_t *)&OHead[p], user_to_olist (U));
    ocntT[p + OLIST_COUNT]++;
  }
}