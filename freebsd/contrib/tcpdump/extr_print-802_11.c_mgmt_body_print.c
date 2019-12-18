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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ FC_PROTECTED (int /*<<< orphan*/ ) ; 
 int FC_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
#define  ST_ACTION 139 
#define  ST_ASSOC_REQUEST 138 
#define  ST_ASSOC_RESPONSE 137 
#define  ST_ATIM 136 
#define  ST_AUTH 135 
#define  ST_BEACON 134 
#define  ST_DEAUTH 133 
#define  ST_DISASSOC 132 
#define  ST_PROBE_REQUEST 131 
#define  ST_PROBE_RESPONSE 130 
#define  ST_REASSOC_REQUEST 129 
#define  ST_REASSOC_RESPONSE 128 
 int handle_action (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_assoc_request (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_assoc_response (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_atim () ; 
 int handle_auth (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_beacon (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_deauth (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_disassoc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_probe_request (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_probe_response (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_reassoc_request (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int handle_reassoc_response (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int wep_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
mgmt_body_print(netdissect_options *ndo,
                uint16_t fc, const uint8_t *src, const u_char *p, u_int length)
{
	ND_PRINT((ndo, "%s", tok2str(st_str, "Unhandled Management subtype(%x)", FC_SUBTYPE(fc))));

	/* There may be a problem w/ AP not having this bit set */
	if (FC_PROTECTED(fc))
		return wep_print(ndo, p);
	switch (FC_SUBTYPE(fc)) {
	case ST_ASSOC_REQUEST:
		return handle_assoc_request(ndo, p, length);
	case ST_ASSOC_RESPONSE:
		return handle_assoc_response(ndo, p, length);
	case ST_REASSOC_REQUEST:
		return handle_reassoc_request(ndo, p, length);
	case ST_REASSOC_RESPONSE:
		return handle_reassoc_response(ndo, p, length);
	case ST_PROBE_REQUEST:
		return handle_probe_request(ndo, p, length);
	case ST_PROBE_RESPONSE:
		return handle_probe_response(ndo, p, length);
	case ST_BEACON:
		return handle_beacon(ndo, p, length);
	case ST_ATIM:
		return handle_atim();
	case ST_DISASSOC:
		return handle_disassoc(ndo, p, length);
	case ST_AUTH:
		return handle_auth(ndo, p, length);
	case ST_DEAUTH:
		return handle_deauth(ndo, src, p, length);
	case ST_ACTION:
		return handle_action(ndo, src, p, length);
	default:
		return 1;
	}
}