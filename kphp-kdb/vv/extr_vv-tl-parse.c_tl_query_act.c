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
struct tl_query_header {int op; int /*<<< orphan*/  qid; } ;
struct connection {int /*<<< orphan*/  In; } ;

/* Variables and functions */
 int RPC_INVOKE_REQ ; 
 int SKIP_ALL_BYTES ; 
 int /*<<< orphan*/  WaitAioArrClear () ; 
 int /*<<< orphan*/  __tl_query_act (struct tl_query_header*) ; 
 scalar_t__ advance_skip_read_ptr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ tl_fetch_error () ; 
 int /*<<< orphan*/  tl_fetch_init (struct connection*,int) ; 
 int /*<<< orphan*/  tl_fetch_query_header (struct tl_query_header*) ; 
 scalar_t__ tl_fetch_unread () ; 
 int /*<<< orphan*/  tl_store_init_keep_error (struct connection*,int /*<<< orphan*/ ) ; 
 struct tl_query_header* zmalloc (int) ; 

int tl_query_act (struct connection *c, int op, int len) {
  if (op != RPC_INVOKE_REQ) {
    return SKIP_ALL_BYTES;
  }
  //WaitAio = WaitAio2 = WaitAio3 = 0;
  //WaitAioArrClear ();
  
  WaitAioArrClear ();
  tl_fetch_init (c, len - 4);
  struct tl_query_header *h = zmalloc (sizeof (*h));
  tl_fetch_query_header (h);
  tl_store_init_keep_error (c, h->qid);
  assert (h->op == op || tl_fetch_error ());

  __tl_query_act (h);
  assert (advance_skip_read_ptr (&c->In, 4 + tl_fetch_unread ()) == 4 + tl_fetch_unread ());
  return 0;
}