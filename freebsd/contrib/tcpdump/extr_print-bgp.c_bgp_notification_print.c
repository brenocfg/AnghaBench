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
typedef  int u_char ;
struct bgp_notification {int const bgpn_major; int const bgpn_minor; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int BGP_NOTIFICATION_SIZE ; 
#define  BGP_NOTIFY_MAJOR_CAP 133 
#define  BGP_NOTIFY_MAJOR_CEASE 132 
#define  BGP_NOTIFY_MAJOR_FSM 131 
#define  BGP_NOTIFY_MAJOR_MSG 130 
#define  BGP_NOTIFY_MAJOR_OPEN 129 
#define  BGP_NOTIFY_MAJOR_UPDATE 128 
 int const BGP_NOTIFY_MINOR_CEASE_MAXPRFX ; 
 int const EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  af_values ; 
 int /*<<< orphan*/  bgp_notify_major_values ; 
 int /*<<< orphan*/  bgp_notify_minor_cap_values ; 
 int /*<<< orphan*/  bgp_notify_minor_cease_values ; 
 int /*<<< orphan*/  bgp_notify_minor_fsm_values ; 
 int /*<<< orphan*/  bgp_notify_minor_msg_values ; 
 int /*<<< orphan*/  bgp_notify_minor_open_values ; 
 int /*<<< orphan*/  bgp_notify_minor_update_values ; 
 int /*<<< orphan*/  bgp_safi_values ; 
 int /*<<< orphan*/  memcpy (struct bgp_notification*,int const*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int const) ; 

__attribute__((used)) static void
bgp_notification_print(netdissect_options *ndo,
                       const u_char *dat, int length)
{
	struct bgp_notification bgpn;
	const u_char *tptr;

	ND_TCHECK2(dat[0], BGP_NOTIFICATION_SIZE);
	memcpy(&bgpn, dat, BGP_NOTIFICATION_SIZE);

        /* some little sanity checking */
        if (length<BGP_NOTIFICATION_SIZE)
            return;

	ND_PRINT((ndo, ", %s (%u)",
	       tok2str(bgp_notify_major_values, "Unknown Error",
			  bgpn.bgpn_major),
	       bgpn.bgpn_major));

        switch (bgpn.bgpn_major) {

        case BGP_NOTIFY_MAJOR_MSG:
            ND_PRINT((ndo, ", subcode %s (%u)",
		   tok2str(bgp_notify_minor_msg_values, "Unknown",
			      bgpn.bgpn_minor),
		   bgpn.bgpn_minor));
            break;
        case BGP_NOTIFY_MAJOR_OPEN:
            ND_PRINT((ndo, ", subcode %s (%u)",
		   tok2str(bgp_notify_minor_open_values, "Unknown",
			      bgpn.bgpn_minor),
		   bgpn.bgpn_minor));
            break;
        case BGP_NOTIFY_MAJOR_UPDATE:
            ND_PRINT((ndo, ", subcode %s (%u)",
		   tok2str(bgp_notify_minor_update_values, "Unknown",
			      bgpn.bgpn_minor),
		   bgpn.bgpn_minor));
            break;
        case BGP_NOTIFY_MAJOR_FSM:
            ND_PRINT((ndo, " subcode %s (%u)",
		   tok2str(bgp_notify_minor_fsm_values, "Unknown",
			      bgpn.bgpn_minor),
		   bgpn.bgpn_minor));
            break;
        case BGP_NOTIFY_MAJOR_CAP:
            ND_PRINT((ndo, " subcode %s (%u)",
		   tok2str(bgp_notify_minor_cap_values, "Unknown",
			      bgpn.bgpn_minor),
		   bgpn.bgpn_minor));
            break;
        case BGP_NOTIFY_MAJOR_CEASE:
            ND_PRINT((ndo, ", subcode %s (%u)",
		   tok2str(bgp_notify_minor_cease_values, "Unknown",
			      bgpn.bgpn_minor),
		   bgpn.bgpn_minor));

	    /* draft-ietf-idr-cease-subcode-02 mentions optionally 7 bytes
             * for the maxprefix subtype, which may contain AFI, SAFI and MAXPREFIXES
             */
	    if(bgpn.bgpn_minor == BGP_NOTIFY_MINOR_CEASE_MAXPRFX && length >= BGP_NOTIFICATION_SIZE + 7) {
		tptr = dat + BGP_NOTIFICATION_SIZE;
		ND_TCHECK2(*tptr, 7);
		ND_PRINT((ndo, ", AFI %s (%u), SAFI %s (%u), Max Prefixes: %u",
		       tok2str(af_values, "Unknown",
				  EXTRACT_16BITS(tptr)),
		       EXTRACT_16BITS(tptr),
		       tok2str(bgp_safi_values, "Unknown", *(tptr+2)),
		       *(tptr+2),
		       EXTRACT_32BITS(tptr+3)));
	    }
            break;
        default:
            break;
        }

	return;
trunc:
	ND_PRINT((ndo, "[|BGP]"));
}