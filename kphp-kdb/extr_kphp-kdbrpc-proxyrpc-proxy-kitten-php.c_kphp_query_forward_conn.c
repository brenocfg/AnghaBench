#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tl_query_header {long long qid; double custom_timeout; long long actor_id; int /*<<< orphan*/  real_op; } ;
struct connection {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* create_rpc_query ) (long long) ;} ;
struct TYPE_6__ {long long id; TYPE_1__ methods; int /*<<< orphan*/  forwarded_queries; int /*<<< orphan*/  timeout; } ;
struct TYPE_5__ {struct tl_query_header* h; } ;

/* Variables and functions */
 TYPE_3__* CC ; 
 TYPE_2__* CQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  forwarded_queries ; 
 int /*<<< orphan*/  stub1 (long long) ; 
 int /*<<< orphan*/  tl_copy_through (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tl_fetch_error () ; 
 int /*<<< orphan*/  tl_fetch_unread () ; 
 int /*<<< orphan*/  tl_store_end_ext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_header (struct tl_query_header*) ; 
 int /*<<< orphan*/  tl_store_init (struct connection*,long long) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,int /*<<< orphan*/ ) ; 

int kphp_query_forward_conn (struct connection *c, long long new_actor_id, long long new_qid, int advance) {
  vkprintf (1, "default_query_forward: CC->id = %lld, CC->timeout = %lf\n", CC->id, CC->timeout);
  assert (c);
  if (tl_fetch_error ()) {
    return -1;
  }
  CC->forwarded_queries ++;
  forwarded_queries ++;
  long long qid = CQ->h->qid;
  double save_timeout = CQ->h->custom_timeout;
  CQ->h->custom_timeout *= 0.9;

  tl_store_init (c, new_qid);

  struct tl_query_header *h = CQ->h;
  assert (h->actor_id == CC->id);
  h->qid = new_qid;
  h->actor_id = new_actor_id;
  tl_store_header (h);
  h->qid = qid;
  h->actor_id = CC->id;
  h->custom_timeout = save_timeout;

  tl_copy_through (tl_fetch_unread (), advance);
  CC->methods.create_rpc_query (new_qid);

  tl_store_end_ext (CQ->h->real_op);
  return 0;
}