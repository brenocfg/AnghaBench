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
struct bgp {int bgp_type; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
#define  BGP_KEEPALIVE 132 
#define  BGP_NOTIFICATION 131 
#define  BGP_OPEN 130 
#define  BGP_ROUTE_REFRESH 129 
 int BGP_SIZE ; 
#define  BGP_UPDATE 128 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  bgp_msg_values ; 
 int /*<<< orphan*/  bgp_notification_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bgp_open_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bgp_route_refresh_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bgp_update_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (struct bgp*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  print_unknown_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
bgp_header_print(netdissect_options *ndo,
                 const u_char *dat, int length)
{
	struct bgp bgp;

	ND_TCHECK2(dat[0], BGP_SIZE);
	memcpy(&bgp, dat, BGP_SIZE);
	ND_PRINT((ndo, "\n\t%s Message (%u), length: %u",
               tok2str(bgp_msg_values, "Unknown", bgp.bgp_type),
               bgp.bgp_type,
               length));

	switch (bgp.bgp_type) {
	case BGP_OPEN:
		bgp_open_print(ndo, dat, length);
		break;
	case BGP_UPDATE:
		bgp_update_print(ndo, dat, length);
		break;
	case BGP_NOTIFICATION:
		bgp_notification_print(ndo, dat, length);
		break;
        case BGP_KEEPALIVE:
                break;
        case BGP_ROUTE_REFRESH:
                bgp_route_refresh_print(ndo, dat, length);
                break;
        default:
                /* we have no decoder for the BGP message */
                ND_TCHECK2(*dat, length);
                ND_PRINT((ndo, "\n\t  no Message %u decoder", bgp.bgp_type));
                print_unknown_data(ndo, dat, "\n\t  ", length);
                break;
	}
	return 1;
trunc:
	ND_PRINT((ndo, "[|BGP]"));
	return 0;
}