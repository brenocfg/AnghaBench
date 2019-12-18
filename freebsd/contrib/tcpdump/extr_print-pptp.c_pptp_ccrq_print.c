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
struct pptp_msg_ccrq {int /*<<< orphan*/  reserved1; int /*<<< orphan*/  call_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pptp_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_ccrq_print(netdissect_options *ndo,
                const u_char *dat)
{
	const struct pptp_msg_ccrq *ptr = (const struct pptp_msg_ccrq *)dat;

	ND_TCHECK(ptr->call_id);
	pptp_call_id_print(ndo, &ptr->call_id);
	ND_TCHECK(ptr->reserved1);

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}