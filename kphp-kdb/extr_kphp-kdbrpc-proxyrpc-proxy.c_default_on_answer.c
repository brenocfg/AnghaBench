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
struct rpc_query {int /*<<< orphan*/  old_qid; int /*<<< orphan*/  pid; int /*<<< orphan*/  in_type; } ;
struct TYPE_4__ {TYPE_1__* h; } ;
struct TYPE_3__ {int /*<<< orphan*/  real_op; } ;

/* Variables and functions */
 TYPE_2__* CQ ; 
 int /*<<< orphan*/  sent_answers ; 
 int /*<<< orphan*/  skipped_answers ; 
 int /*<<< orphan*/  tl_copy_through (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tl_fetch_unread () ; 
 scalar_t__ tl_init_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end_ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_header (TYPE_1__*) ; 

void default_on_answer (struct rpc_query *q) {
  if (tl_init_store (q->in_type, /*q->in,*/ &q->pid, q->old_qid) < 0) {
    skipped_answers ++;
    return;
  }
  tl_store_header (CQ->h);
  sent_answers ++;

  //rwm_check (TL_OUT_RAW_MSG);
  tl_copy_through (tl_fetch_unread (), 1);
  //rwm_check (TL_OUT_RAW_MSG);
  tl_store_end_ext (CQ->h->real_op);
}