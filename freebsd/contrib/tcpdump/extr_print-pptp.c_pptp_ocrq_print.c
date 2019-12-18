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
struct pptp_msg_ocrq {int /*<<< orphan*/ * subaddr; int /*<<< orphan*/ * phone_no; int /*<<< orphan*/ * reserved1; int /*<<< orphan*/ * phone_no_len; int /*<<< orphan*/ * pkt_proc_delay; int /*<<< orphan*/ * recv_winsiz; int /*<<< orphan*/ * framing_type; int /*<<< orphan*/ * bearer_type; int /*<<< orphan*/ * max_bps; int /*<<< orphan*/ * min_bps; int /*<<< orphan*/ * call_ser; int /*<<< orphan*/ * call_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_bearer_type_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_call_ser_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_framing_type_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_pkt_proc_delay_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_recv_winsiz_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_subaddr_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_ocrq_print(netdissect_options *ndo,
                const u_char *dat)
{
	const struct pptp_msg_ocrq *ptr = (const struct pptp_msg_ocrq *)dat;

	ND_TCHECK(ptr->call_id);
	pptp_call_id_print(ndo, &ptr->call_id);
	ND_TCHECK(ptr->call_ser);
	pptp_call_ser_print(ndo, &ptr->call_ser);
	ND_TCHECK(ptr->min_bps);
	ND_PRINT((ndo, " MIN_BPS(%u)", EXTRACT_32BITS(&ptr->min_bps)));
	ND_TCHECK(ptr->max_bps);
	ND_PRINT((ndo, " MAX_BPS(%u)", EXTRACT_32BITS(&ptr->max_bps)));
	ND_TCHECK(ptr->bearer_type);
	pptp_bearer_type_print(ndo, &ptr->bearer_type);
	ND_TCHECK(ptr->framing_type);
	pptp_framing_type_print(ndo, &ptr->framing_type);
	ND_TCHECK(ptr->recv_winsiz);
	pptp_recv_winsiz_print(ndo, &ptr->recv_winsiz);
	ND_TCHECK(ptr->pkt_proc_delay);
	pptp_pkt_proc_delay_print(ndo, &ptr->pkt_proc_delay);
	ND_TCHECK(ptr->phone_no_len);
	ND_PRINT((ndo, " PHONE_NO_LEN(%u)", EXTRACT_16BITS(&ptr->phone_no_len)));
	ND_TCHECK(ptr->reserved1);
	ND_TCHECK(ptr->phone_no);
	ND_PRINT((ndo, " PHONE_NO(%.64s)", ptr->phone_no));
	ND_TCHECK(ptr->subaddr);
	pptp_subaddr_print(ndo, &ptr->subaddr[0]);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}