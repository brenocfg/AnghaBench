#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  last_action_time; } ;
typedef  TYPE_1__ host_t ;

/* Variables and functions */
 TYPE_1__* get_host_by_connection (struct connection*) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int rpc_execute_ping (struct connection *c) {
  host_t *H = get_host_by_connection (c);
  if (H == NULL) {
    vkprintf (1, "rpc_execute_ping: get_host_by_connection returns NULL.\n");
    return -__LINE__;
  }
  H->last_action_time = now;
  return 0;
}