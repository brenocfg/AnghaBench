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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct conn_target {int port; TYPE_1__ target; } ;

/* Variables and functions */
 int get_target_impl (struct conn_target*) ; 
 int /*<<< orphan*/  htonl (int) ; 

int get_target_by_pid (int ip, int port, struct conn_target *ct) {
  ct->target.s_addr = htonl (ip);
  ct->port = port;

  return get_target_impl (ct);
}