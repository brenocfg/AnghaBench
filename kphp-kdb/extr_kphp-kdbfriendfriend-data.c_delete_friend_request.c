#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ req_cnt; void* req_time_tree; void* req_tree; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_6__ {int date; } ;
typedef  TYPE_2__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 void* tree_delete (void*,int) ; 
 TYPE_2__* tree_lookup (void*,int) ; 

__attribute__((used)) static int delete_friend_request (user_t *U, int friend_id) {
  tree_t *P;
  if (!U || friend_id <= 0) {
    return -1;
  }
  P = tree_lookup (U->req_tree, friend_id);
  if (P) {
    int date = P->date;
    U->req_tree = tree_delete (U->req_tree, friend_id);
    U->req_time_tree = tree_delete (U->req_time_tree, -date);
    U->req_cnt--;
    assert (U->req_cnt >= 0);
    return 1;
  }
  return 0;
}