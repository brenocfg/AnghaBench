#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int user_id; scalar_t__ req_cnt; scalar_t__ fr_cnt; scalar_t__ pr_tree; scalar_t__ req_time_tree; scalar_t__ req_tree; scalar_t__ fr_tree; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 TYPE_1__** User ; 
 int conv_uid (int) ; 
 int /*<<< orphan*/  free_friend_list (TYPE_1__*) ; 
 int /*<<< orphan*/  free_privacy_tree (scalar_t__) ; 
 int /*<<< orphan*/  free_tree (scalar_t__) ; 
 int /*<<< orphan*/  free_user_struct (TYPE_1__*) ; 
 int ignored_delete_user_id ; 
 int /*<<< orphan*/  tot_users ; 

__attribute__((used)) static int delete_user (int user_id) {
  int i = conv_uid (user_id);
  user_t *U;
  if (i < 0 || user_id == ignored_delete_user_id) {
    return -1;
  }
  if (!User[i]) {
    return 0;
  }
  U = User[i];
  User[i] = 0;

  //free_tree (U->fr_tree);
  free_friend_list (U);
  free_tree (U->req_tree);
  free_tree (U->req_time_tree);
  free_privacy_tree (U->pr_tree);

  U->fr_tree = 0;
  U->req_tree = 0;
  U->req_time_tree = 0;
  U->pr_tree = 0;
  U->fr_cnt = 0;
  U->req_cnt = 0;
  U->user_id = -1;

  free_user_struct (U);
  tot_users--;

  return 1;
}