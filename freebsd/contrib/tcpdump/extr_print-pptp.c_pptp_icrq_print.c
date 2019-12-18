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
struct pptp_msg_icrq {int /*<<< orphan*/ * subaddr; int /*<<< orphan*/ * dialing_no; int /*<<< orphan*/ * dialed_no; int /*<<< orphan*/ * dialing_no_len; int /*<<< orphan*/ * dialed_no_len; int /*<<< orphan*/ * phy_chan_id; int /*<<< orphan*/ * bearer_type; int /*<<< orphan*/ * call_ser; int /*<<< orphan*/ * call_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_bearer_type_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_call_ser_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_phy_chan_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_subaddr_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_icrq_print(netdissect_options *ndo,
                const u_char *dat)
{
	const struct pptp_msg_icrq *ptr = (const struct pptp_msg_icrq *)dat;

	ND_TCHECK(ptr->call_id);
	pptp_call_id_print(ndo, &ptr->call_id);
	ND_TCHECK(ptr->call_ser);
	pptp_call_ser_print(ndo, &ptr->call_ser);
	ND_TCHECK(ptr->bearer_type);
	pptp_bearer_type_print(ndo, &ptr->bearer_type);
	ND_TCHECK(ptr->phy_chan_id);
	pptp_phy_chan_id_print(ndo, &ptr->phy_chan_id);
	ND_TCHECK(ptr->dialed_no_len);
	ND_PRINT((ndo, " DIALED_NO_LEN(%u)", EXTRACT_16BITS(&ptr->dialed_no_len)));
	ND_TCHECK(ptr->dialing_no_len);
	ND_PRINT((ndo, " DIALING_NO_LEN(%u)", EXTRACT_16BITS(&ptr->dialing_no_len)));
	ND_TCHECK(ptr->dialed_no);
	ND_PRINT((ndo, " DIALED_NO(%.64s)", ptr->dialed_no));
	ND_TCHECK(ptr->dialing_no);
	ND_PRINT((ndo, " DIALING_NO(%.64s)", ptr->dialing_no));
	ND_TCHECK(ptr->subaddr);
	pptp_subaddr_print(ndo, &ptr->subaddr[0]);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}