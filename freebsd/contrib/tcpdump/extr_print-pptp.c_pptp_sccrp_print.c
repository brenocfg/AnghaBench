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
struct pptp_msg_sccrp {int /*<<< orphan*/ * vendor; int /*<<< orphan*/ * hostname; int /*<<< orphan*/ * firm_rev; int /*<<< orphan*/ * max_channel; int /*<<< orphan*/ * bearer_cap; int /*<<< orphan*/ * framing_cap; int /*<<< orphan*/ * err_code; int /*<<< orphan*/ * result_code; int /*<<< orphan*/ * proto_ver; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PPTP_CTRL_MSG_TYPE_SCCRP ; 
 int /*<<< orphan*/  pptp_bearer_cap_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_err_code_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_firm_rev_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_framing_cap_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_hostname_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_max_channel_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_proto_ver_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pptp_result_code_print (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pptp_vendor_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_sccrp_print(netdissect_options *ndo,
                 const u_char *dat)
{
	const struct pptp_msg_sccrp *ptr = (const struct pptp_msg_sccrp *)dat;

	ND_TCHECK(ptr->proto_ver);
	pptp_proto_ver_print(ndo, &ptr->proto_ver);
	ND_TCHECK(ptr->result_code);
	pptp_result_code_print(ndo, &ptr->result_code, PPTP_CTRL_MSG_TYPE_SCCRP);
	ND_TCHECK(ptr->err_code);
	pptp_err_code_print(ndo, &ptr->err_code);
	ND_TCHECK(ptr->framing_cap);
	pptp_framing_cap_print(ndo, &ptr->framing_cap);
	ND_TCHECK(ptr->bearer_cap);
	pptp_bearer_cap_print(ndo, &ptr->bearer_cap);
	ND_TCHECK(ptr->max_channel);
	pptp_max_channel_print(ndo, &ptr->max_channel);
	ND_TCHECK(ptr->firm_rev);
	pptp_firm_rev_print(ndo, &ptr->firm_rev);
	ND_TCHECK(ptr->hostname);
	pptp_hostname_print(ndo, &ptr->hostname[0]);
	ND_TCHECK(ptr->vendor);
	pptp_vendor_print(ndo, &ptr->vendor[0]);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}