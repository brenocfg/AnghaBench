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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  TYPE_1__* ng_l2cap_con_p ;
struct TYPE_3__ {int /*<<< orphan*/  rx_pkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_FREE_M (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ng_l2cap_process_cmd_urs(ng_l2cap_con_p con, uint8_t ident)
{
	/* We only support master side yet .*/
	//send_l2cap_reject(con,ident ... );
	
	NG_FREE_M(con->rx_pkt);
	return 0;
}