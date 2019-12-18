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
typedef  int /*<<< orphan*/  listree_t ;

/* Variables and functions */
 scalar_t__ R_cnt ; 
 int /*<<< orphan*/  assert (int) ; 
 int listree_get_pos (int /*<<< orphan*/ *,int,int) ; 
 int listree_get_size (int /*<<< orphan*/ *) ; 
 int prepare_peer_msglist (int,int,int /*<<< orphan*/ *) ; 

int get_peer_msglist_pos (int user_id, int peer_id, int local_id) {
  static listree_t X;
  int S;

  R_cnt = 0;

  int res = prepare_peer_msglist (user_id, peer_id, &X);
  if (res <= 0) {
    return res;
  }

  S = listree_get_size (&X);
  assert (S >= 0);
  if (!S) {
    return 0;
  }

  res = listree_get_pos (&X, local_id, 1) + 1;

  assert (res >= 0 && res <= S);
  return res;
}