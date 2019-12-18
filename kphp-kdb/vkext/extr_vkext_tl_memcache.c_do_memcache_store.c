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
struct rpc_connection {int dummy; } ;
struct memcache_value {int dummy; } ;

/* Variables and functions */
 int MEMCACHE_ADD ; 
 int MEMCACHE_REPLACE ; 
 int MEMCACHE_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 struct memcache_value do_memcache_act (struct rpc_connection*,long long,int,double) ; 
 long long do_memcache_send_store (struct rpc_connection*,char const*,int,char const*,int,int,int,int,double) ; 

struct memcache_value do_memcache_store (struct rpc_connection *c, const char *key, int key_len, const char *value, int value_len, int flags, int delay, int op, double timeout) {
  assert (op == MEMCACHE_SET || op == MEMCACHE_REPLACE || op == MEMCACHE_ADD);
  long long qid = do_memcache_send_store (c, key, key_len, value, value_len, flags, delay, op, timeout);
  return do_memcache_act (c, qid, 1, timeout);
}