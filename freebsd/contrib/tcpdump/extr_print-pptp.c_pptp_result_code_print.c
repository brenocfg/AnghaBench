#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct tok {int dummy; } ;
struct TYPE_4__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int PPTP_CTRL_MSG_TYPE_CDN ; 
 int PPTP_CTRL_MSG_TYPE_ECHORP ; 
 int PPTP_CTRL_MSG_TYPE_ICRP ; 
 int PPTP_CTRL_MSG_TYPE_OCRP ; 
 int PPTP_CTRL_MSG_TYPE_SCCRP ; 
 int PPTP_CTRL_MSG_TYPE_StopCCRP ; 
 struct tok* pptp_cdn_str ; 
 struct tok* pptp_echorp_str ; 
 struct tok* pptp_icrp_str ; 
 struct tok* pptp_ocrp_str ; 
 struct tok* pptp_scrrp_str ; 
 int /*<<< orphan*/  tok2str (struct tok const*,char*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
pptp_result_code_print(netdissect_options *ndo,
                       const uint8_t *result_code, int ctrl_msg_type)
{
	ND_PRINT((ndo, " RESULT_CODE(%u", *result_code));
	if (ndo->ndo_vflag) {
		const struct tok *dict =
			ctrl_msg_type == PPTP_CTRL_MSG_TYPE_SCCRP    ? pptp_scrrp_str :
			ctrl_msg_type == PPTP_CTRL_MSG_TYPE_StopCCRP ? pptp_echorp_str :
			ctrl_msg_type == PPTP_CTRL_MSG_TYPE_ECHORP   ? pptp_echorp_str :
			ctrl_msg_type == PPTP_CTRL_MSG_TYPE_OCRP     ? pptp_ocrp_str :
			ctrl_msg_type == PPTP_CTRL_MSG_TYPE_ICRP     ? pptp_icrp_str :
			ctrl_msg_type == PPTP_CTRL_MSG_TYPE_CDN      ? pptp_cdn_str :
			NULL; /* assertion error */
		if (dict != NULL)
			ND_PRINT((ndo, ":%s", tok2str(dict, "?", *result_code)));
	}
	ND_PRINT((ndo, ")"));
}