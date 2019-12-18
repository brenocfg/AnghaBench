#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct connection {TYPE_2__* fd; } ;
struct TYPE_7__ {TYPE_1__* h; } ;
struct TYPE_6__ {int /*<<< orphan*/  new_id; } ;
struct TYPE_5__ {scalar_t__ kitten_php_delay; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
 TYPE_2__* CC ; 
 TYPE_3__* CQ ; 
 long long get_free_rpc_qid (int /*<<< orphan*/ ) ; 
 int kitten_php_delay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct connection* kitten_php_get_connection (int) ; 
 int kphp_query_forward_conn (struct connection*,int /*<<< orphan*/ ,long long,int) ; 
 scalar_t__ tl_fetch_error () ; 
 int /*<<< orphan*/  vkprintf (int,char*,TYPE_2__*) ; 

int kitten_php_forward (void) {
  vkprintf (2, "forward: CC = %p\n", CC);
  if (tl_fetch_error ()) {
    return -1;
  }
  if (CQ->h->kitten_php_delay > 0) {
    return kitten_php_delay (0, 0);
  }
  struct connection *c = kitten_php_get_connection (1);
  if (c) {
    vkprintf (2, "Forwarding: connect = %d\n", c->fd); 
    long long new_qid = get_free_rpc_qid (CQ->h->qid);
    return kphp_query_forward_conn (c, CC->new_id, new_qid, 1);
  } else {
    return -1;
  }
}