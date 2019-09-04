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
struct TYPE_2__ {int /*<<< orphan*/  total_bytes; } ;
struct udp_msg {int /*<<< orphan*/  S; TYPE_1__ raw; } ;
struct tl_query_header {scalar_t__ op; int /*<<< orphan*/  qid; } ;
struct raw_message {int dummy; } ;

/* Variables and functions */
 scalar_t__ RPC_INVOKE_REQ ; 
 int /*<<< orphan*/  WaitAioArrClear () ; 
 int /*<<< orphan*/  __tl_query_act (struct tl_query_header*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwm_clone (struct raw_message*,TYPE_1__*) ; 
 int /*<<< orphan*/  rwm_free (struct raw_message*) ; 
 int /*<<< orphan*/  tl_fetch_init_raw_message (struct raw_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_query_header (struct tl_query_header*) ; 
 int /*<<< orphan*/  tl_store_init_raw_msg_keep_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tl_query_header* zmalloc (int) ; 

int tl_query_act_udp (struct udp_msg *msg) {
  //WaitAio = WaitAio2 = WaitAio3 = 0;
  //WaitAioArrClear ();
  
  WaitAioArrClear ();
  struct raw_message r;
  rwm_clone (&r, &msg->raw);
  tl_fetch_init_raw_message (&r, msg->raw.total_bytes);
  rwm_free (&r);
  struct tl_query_header *h = zmalloc (sizeof (*h));
  tl_fetch_query_header (h);
  assert (msg->S);
  tl_store_init_raw_msg_keep_error (msg->S, h->qid);

  if (h->op != RPC_INVOKE_REQ) {
    return 0;
  }

  __tl_query_act (h);
  return 0;
}