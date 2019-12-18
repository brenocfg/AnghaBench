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
struct pptp_msg_echorp {int /*<<< orphan*/  reserved1; int /*<<< orphan*/  err_code; int /*<<< orphan*/  result_code; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPTP_CTRL_MSG_TYPE_ECHORP ; 
 int /*<<< orphan*/  pptp_err_code_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_result_code_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_echorp_print(netdissect_options *ndo,
                  const u_char *dat)
{
	const struct pptp_msg_echorp *ptr = (const struct pptp_msg_echorp *)dat;

	ND_TCHECK(ptr->id);
	pptp_id_print(ndo, &ptr->id);
	ND_TCHECK(ptr->result_code);
	pptp_result_code_print(ndo, &ptr->result_code, PPTP_CTRL_MSG_TYPE_ECHORP);
	ND_TCHECK(ptr->err_code);
	pptp_err_code_print(ndo, &ptr->err_code);
	ND_TCHECK(ptr->reserved1);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}