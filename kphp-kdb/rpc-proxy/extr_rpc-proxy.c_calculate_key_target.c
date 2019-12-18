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
typedef  void rpc_cluster_bucket ;
struct TYPE_3__ {int /*<<< orphan*/ * fun_pos; } ;
struct TYPE_4__ {TYPE_1__ methods; } ;

/* Variables and functions */
 TYPE_2__* CC ; 
 int RPC_FUN_START (int /*<<< orphan*/ ,void**) ; 
 size_t RPC_FUN_STRING_FORWARD ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*,int) ; 

struct rpc_cluster_bucket *calculate_key_target (const char *key, int key_len) {
  vkprintf (3, "calculate_key_target: key = %s, key_len = %d\n", key, key_len);
  void *T[3];
  T[0] = (void *)key;
  T[1] = (void *)(long)key_len;
  T[2] = 0;
  int r = RPC_FUN_START(CC->methods.fun_pos[RPC_FUN_STRING_FORWARD], T);
  if (r < 0) { return 0; }
  return T[2];
}