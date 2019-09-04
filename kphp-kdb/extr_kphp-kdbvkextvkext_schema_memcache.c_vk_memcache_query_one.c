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
typedef  int /*<<< orphan*/  zval ;
struct rpc_query {int /*<<< orphan*/  extra_free; void* extra; } ;
struct rpc_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  END_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  START_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _extra_dec_ref ; 
 int /*<<< orphan*/  do_rpc_clean () ; 
 struct rpc_query* do_rpc_send_noflush (struct rpc_connection*,double) ; 
 void* store_function (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  tmp ; 
 int /*<<< orphan*/  total_tl_working ; 

struct rpc_query *vk_memcache_query_one (struct rpc_connection *c, double timeout, zval **arr) {
  do_rpc_clean ();
  START_TIMER (tmp);
  void *res = store_function (arr);
  END_TIMER (tmp);
  if (!res) { return 0; }
  struct rpc_query *q;
  if (!(q = do_rpc_send_noflush (c, timeout))) {
    return 0;
  }
  q->extra = res;
  q->extra_free = _extra_dec_ref;
  total_tl_working ++;
  return q;
}