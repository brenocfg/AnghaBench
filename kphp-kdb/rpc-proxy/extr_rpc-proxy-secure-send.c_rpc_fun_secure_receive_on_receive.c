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
struct tree_secure_receive_answer {struct secure_receive_answer* x; } ;
struct secure_receive_answer {int /*<<< orphan*/  answer_op; int /*<<< orphan*/  answer_len; int /*<<< orphan*/  answer; scalar_t__ h; int /*<<< orphan*/  pid; int /*<<< orphan*/  qid; } ;
struct TYPE_4__ {TYPE_1__* h; int /*<<< orphan*/ * remote_pid; int /*<<< orphan*/  in_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 TYPE_2__* CQ ; 
 int /*<<< orphan*/  RPC_FUN_NEXT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secure_receive_answer_tree ; 
 int /*<<< orphan*/  tl_init_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_end_ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_header (scalar_t__) ; 
 int /*<<< orphan*/  tl_store_raw_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tree_secure_receive_answer* tree_lookup_secure_receive_answer (int /*<<< orphan*/ ,struct secure_receive_answer*) ; 

int rpc_fun_secure_receive_on_receive (void **IP, void **Data) {
  struct secure_receive_answer t;
  t.qid = CQ->h->qid;
  t.pid = *CQ->remote_pid;
  struct tree_secure_receive_answer *T = tree_lookup_secure_receive_answer (secure_receive_answer_tree, &t);
  if (!T) {
    RPC_FUN_NEXT;
  } else {
    struct secure_receive_answer *A = T->x;
    assert (A->answer);
    tl_init_store (CQ->in_type, CQ->remote_pid, CQ->h->qid);
    //tl_store_init_any (CQ->in_type, CQ->in, CQ->h->qid);
    if (A->h) {
      tl_store_header (A->h);
    }
    tl_store_raw_data (A->answer, A->answer_len);
    tl_store_end_ext (A->answer_op);
    return -1;
  }
}