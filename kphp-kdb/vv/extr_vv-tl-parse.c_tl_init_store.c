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
struct udp_target {int /*<<< orphan*/  state; } ;
struct process_id {int dummy; } ;
struct connection {int dummy; } ;
typedef  enum tl_type { ____Placeholder_tl_type } tl_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct connection* rpc_target_choose_connection (int /*<<< orphan*/ ,struct process_id*) ; 
 int /*<<< orphan*/  rpc_target_lookup (struct process_id*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_store_init (struct connection*,long long) ; 
 int /*<<< orphan*/  tl_store_init_raw_msg (struct udp_target*,long long) ; 
 int /*<<< orphan*/  tl_store_init_tcp_raw_msg (struct connection*,long long) ; 
#define  tl_type_conn 130 
#define  tl_type_raw_msg 129 
#define  tl_type_tcp_raw_msg 128 
 int /*<<< orphan*/  udp_failed ; 
 struct udp_target* udp_target_lookup (struct process_id*) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int tl_init_store (enum tl_type type, struct process_id *pid, long long qid) {
  switch (type) {
  case tl_type_conn:
    {
      struct connection *d = rpc_target_choose_connection (rpc_target_lookup (pid), pid);
      if (d) {
        vkprintf (2, "Good connection\n");
        tl_store_init (d, qid);
        return 1;
      } else {
        vkprintf (2, "Bad connection\n");
        return -1;
      }
    }
  case tl_type_raw_msg:
    {
      struct udp_target *S = udp_target_lookup (pid);
      if (S && S->state != udp_failed) {
        tl_store_init_raw_msg (S, qid);
        return 1;
      } else {
        return -1;
      }
    }
  case tl_type_tcp_raw_msg:
    {
      struct connection *d = rpc_target_choose_connection (rpc_target_lookup (pid), pid);
      if (d) {
        vkprintf (2, "Good connection\n");
        tl_store_init_tcp_raw_msg (d, qid);
        return 1;
      } else {
        vkprintf (2, "Bad connection\n");
        return -1;
      }
    }
  default:
    fprintf (stderr, "type = %d\n", type);
    assert (0);
    return 0;
  }
}