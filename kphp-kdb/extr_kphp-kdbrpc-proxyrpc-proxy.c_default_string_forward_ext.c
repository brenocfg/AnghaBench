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
struct rpc_cluster_bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_KEY_LEN ; 
 int /*<<< orphan*/  TL_ERROR_PROXY_NO_TARGET ; 
 struct rpc_cluster_bucket* calculate_key_target (char*,int) ; 
 int query_forward (struct rpc_cluster_bucket) ; 
 int /*<<< orphan*/  tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_mark_delete () ; 
 int /*<<< orphan*/  tl_fetch_mark_restore () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 int tl_fetch_string0 (char*,int /*<<< orphan*/ ) ; 

int default_string_forward_ext (void) {
  tl_fetch_int (); //op
  int key_len;
  char key[MAX_KEY_LEN + 1];
  key_len = tl_fetch_string0 (key, MAX_KEY_LEN);
  if (key_len < 0) {
    tl_fetch_mark_delete ();
    return -1;
  }
  tl_fetch_mark_restore ();
  struct rpc_cluster_bucket *B = calculate_key_target (key, key_len);
  if (!B) {
    tl_fetch_set_error_format (TL_ERROR_PROXY_NO_TARGET, "Can not find target for key %.*s%s", key_len <= 30 ? key_len : 27, key, key_len <= 30 ? "" : "...");
    return -1;
  }
  return query_forward (*B);
}