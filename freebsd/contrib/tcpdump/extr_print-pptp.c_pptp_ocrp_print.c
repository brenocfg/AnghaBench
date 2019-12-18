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
struct pptp_msg_ocrp {int /*<<< orphan*/  phy_chan_id; int /*<<< orphan*/  pkt_proc_delay; int /*<<< orphan*/  recv_winsiz; int /*<<< orphan*/  conn_speed; int /*<<< orphan*/  cause_code; int /*<<< orphan*/  err_code; int /*<<< orphan*/  result_code; int /*<<< orphan*/  peer_call_id; int /*<<< orphan*/  call_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPTP_CTRL_MSG_TYPE_OCRP ; 
 int /*<<< orphan*/  pptp_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_cause_code_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_conn_speed_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_err_code_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_peer_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_phy_chan_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_pkt_proc_delay_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_recv_winsiz_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_result_code_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_ocrp_print(netdissect_options *ndo,
                const u_char *dat)
{
	const struct pptp_msg_ocrp *ptr = (const struct pptp_msg_ocrp *)dat;

	ND_TCHECK(ptr->call_id);
	pptp_call_id_print(ndo, &ptr->call_id);
	ND_TCHECK(ptr->peer_call_id);
	pptp_peer_call_id_print(ndo, &ptr->peer_call_id);
	ND_TCHECK(ptr->result_code);
	pptp_result_code_print(ndo, &ptr->result_code, PPTP_CTRL_MSG_TYPE_OCRP);
	ND_TCHECK(ptr->err_code);
	pptp_err_code_print(ndo, &ptr->err_code);
	ND_TCHECK(ptr->cause_code);
	pptp_cause_code_print(ndo, &ptr->cause_code);
	ND_TCHECK(ptr->conn_speed);
	pptp_conn_speed_print(ndo, &ptr->conn_speed);
	ND_TCHECK(ptr->recv_winsiz);
	pptp_recv_winsiz_print(ndo, &ptr->recv_winsiz);
	ND_TCHECK(ptr->pkt_proc_delay);
	pptp_pkt_proc_delay_print(ndo, &ptr->pkt_proc_delay);
	ND_TCHECK(ptr->phy_chan_id);
	pptp_phy_chan_id_print(ndo, &ptr->phy_chan_id);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}