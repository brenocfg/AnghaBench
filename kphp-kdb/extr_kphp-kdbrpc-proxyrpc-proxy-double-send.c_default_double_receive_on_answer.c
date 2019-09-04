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
struct rpc_query {scalar_t__ in_type; int /*<<< orphan*/  old_qid; int /*<<< orphan*/  pid; } ;
struct connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 TYPE_1__* CQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int rpc_target_choose_random_connections (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct connection**) ; 
 int /*<<< orphan*/  rpc_target_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sent_answers ; 
 int /*<<< orphan*/  skipped_answers ; 
 int /*<<< orphan*/  tl_copy_through (int,int) ; 
 int tl_fetch_move (int) ; 
 int tl_fetch_unread () ; 
 scalar_t__ tl_init_store (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int /*<<< orphan*/  tl_store_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_init (struct connection*,int /*<<< orphan*/ ) ; 
 scalar_t__ tl_type_conn ; 

void default_double_receive_on_answer (struct rpc_query *q) {
  struct connection *ca[3];
  int t = rpc_target_choose_random_connections (rpc_target_lookup (&q->pid), &q->pid, 2, ca);
  if (t >= 0 && q->in_type == tl_type_conn) {
    int i;
    int p = tl_fetch_unread ();
    for (i = 0; i < t; i ++) {
      struct connection *d = ca[i];
      tl_store_init (d, q->old_qid);
      tl_store_header (CQ->h);
      tl_copy_through (tl_fetch_unread (), 0);
      tl_store_end ();
    }
    sent_answers ++;
    assert (tl_fetch_move (p) == p);
  } else {
    if (tl_init_store (q->in_type, /*q->in,*/ &q->pid, q->old_qid) < 0) {
      skipped_answers ++;
      return;
    }
    tl_store_header (CQ->h);
    sent_answers ++;

    tl_copy_through (tl_fetch_unread (), 1);
    tl_store_end ();
  }
}