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
typedef  int /*<<< orphan*/  u_char ;
struct pptp_msg_iccn {int /*<<< orphan*/  framing_type; int /*<<< orphan*/  pkt_proc_delay; int /*<<< orphan*/  recv_winsiz; int /*<<< orphan*/  conn_speed; int /*<<< orphan*/  reserved1; int /*<<< orphan*/  peer_call_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pptp_conn_speed_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_framing_type_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_peer_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_pkt_proc_delay_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_recv_winsiz_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_iccn_print(netdissect_options *ndo,
                const u_char *dat)
{
	const struct pptp_msg_iccn *ptr = (const struct pptp_msg_iccn *)dat;

	ND_TCHECK(ptr->peer_call_id);
	pptp_peer_call_id_print(ndo, &ptr->peer_call_id);
	ND_TCHECK(ptr->reserved1);
	ND_TCHECK(ptr->conn_speed);
	pptp_conn_speed_print(ndo, &ptr->conn_speed);
	ND_TCHECK(ptr->recv_winsiz);
	pptp_recv_winsiz_print(ndo, &ptr->recv_winsiz);
	ND_TCHECK(ptr->pkt_proc_delay);
	pptp_pkt_proc_delay_print(ndo, &ptr->pkt_proc_delay);
	ND_TCHECK(ptr->framing_type);
	pptp_framing_type_print(ndo, &ptr->framing_type);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}