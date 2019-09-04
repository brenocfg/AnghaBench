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
struct connection {int dummy; } ;
struct conn_target {int dummy; } ;

/* Variables and functions */
 struct conn_target* Targets ; 
 struct connection* get_target_connection (struct conn_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_send_lease_stats (struct connection*) ; 

void rpct_lease_stats (int target_fd) {
  if (target_fd == -1) {
    return;
  }
  struct conn_target *target = &Targets[target_fd];
  struct connection *conn = get_target_connection (target, 0);
  if (conn != NULL) {
    rpc_send_lease_stats (conn);
  }
}