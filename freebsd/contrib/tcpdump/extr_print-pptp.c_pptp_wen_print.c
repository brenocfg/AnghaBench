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
struct pptp_msg_wen {int /*<<< orphan*/  align_err; int /*<<< orphan*/  timeout_err; int /*<<< orphan*/  buffer_overrun; int /*<<< orphan*/  hardware_overrun; int /*<<< orphan*/  framing_err; int /*<<< orphan*/  crc_err; int /*<<< orphan*/  reserved1; int /*<<< orphan*/  peer_call_id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pptp_peer_call_id_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
pptp_wen_print(netdissect_options *ndo,
               const u_char *dat)
{
	const struct pptp_msg_wen *ptr = (const struct pptp_msg_wen *)dat;

	ND_TCHECK(ptr->peer_call_id);
	pptp_peer_call_id_print(ndo, &ptr->peer_call_id);
	ND_TCHECK(ptr->reserved1);
	ND_TCHECK(ptr->crc_err);
	ND_PRINT((ndo, " CRC_ERR(%u)", EXTRACT_32BITS(&ptr->crc_err)));
	ND_TCHECK(ptr->framing_err);
	ND_PRINT((ndo, " FRAMING_ERR(%u)", EXTRACT_32BITS(&ptr->framing_err)));
	ND_TCHECK(ptr->hardware_overrun);
	ND_PRINT((ndo, " HARDWARE_OVERRUN(%u)", EXTRACT_32BITS(&ptr->hardware_overrun)));
	ND_TCHECK(ptr->buffer_overrun);
	ND_PRINT((ndo, " BUFFER_OVERRUN(%u)", EXTRACT_32BITS(&ptr->buffer_overrun)));
	ND_TCHECK(ptr->timeout_err);
	ND_PRINT((ndo, " TIMEOUT_ERR(%u)", EXTRACT_32BITS(&ptr->timeout_err)));
	ND_TCHECK(ptr->align_err);
	ND_PRINT((ndo, " ALIGN_ERR(%u)", EXTRACT_32BITS(&ptr->align_err)));

	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
}