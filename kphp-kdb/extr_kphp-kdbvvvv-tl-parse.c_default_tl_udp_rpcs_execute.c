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
struct udp_msg {TYPE_1__* S; } ;
struct TYPE_2__ {int /*<<< orphan*/  PID; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TL_IN_PID ; 
 int /*<<< orphan*/  WaitAioArrClear () ; 
 int /*<<< orphan*/  tl_query_act_udp (struct udp_msg*) ; 

int default_tl_udp_rpcs_execute (struct udp_msg *msg) {  
  WaitAioArrClear ();
  TL_IN_PID = &msg->S->PID;
  tl_query_act_udp (msg);
  return 0;
}