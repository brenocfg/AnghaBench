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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR1 ; 
 int /*<<< orphan*/  ADDR2 ; 
 int /*<<< orphan*/  ADDR3 ; 
 int /*<<< orphan*/  ADDR4 ; 
 scalar_t__ DATA_FRAME_IS_CF_ACK (int /*<<< orphan*/ ) ; 
 scalar_t__ DATA_FRAME_IS_CF_POLL (int /*<<< orphan*/ ) ; 
 scalar_t__ DATA_FRAME_IS_QOS (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_FROM_DS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ FC_TO_DS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etheraddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
data_header_print(netdissect_options *ndo, uint16_t fc, const u_char *p)
{
	u_int subtype = FC_SUBTYPE(fc);

	if (DATA_FRAME_IS_CF_ACK(subtype) || DATA_FRAME_IS_CF_POLL(subtype) ||
	    DATA_FRAME_IS_QOS(subtype)) {
		ND_PRINT((ndo, "CF "));
		if (DATA_FRAME_IS_CF_ACK(subtype)) {
			if (DATA_FRAME_IS_CF_POLL(subtype))
				ND_PRINT((ndo, "Ack/Poll"));
			else
				ND_PRINT((ndo, "Ack"));
		} else {
			if (DATA_FRAME_IS_CF_POLL(subtype))
				ND_PRINT((ndo, "Poll"));
		}
		if (DATA_FRAME_IS_QOS(subtype))
			ND_PRINT((ndo, "+QoS"));
		ND_PRINT((ndo, " "));
	}

#define ADDR1  (p + 4)
#define ADDR2  (p + 10)
#define ADDR3  (p + 16)
#define ADDR4  (p + 24)

	if (!FC_TO_DS(fc) && !FC_FROM_DS(fc)) {
		ND_PRINT((ndo, "DA:%s SA:%s BSSID:%s ",
		    etheraddr_string(ndo, ADDR1), etheraddr_string(ndo, ADDR2),
		    etheraddr_string(ndo, ADDR3)));
	} else if (!FC_TO_DS(fc) && FC_FROM_DS(fc)) {
		ND_PRINT((ndo, "DA:%s BSSID:%s SA:%s ",
		    etheraddr_string(ndo, ADDR1), etheraddr_string(ndo, ADDR2),
		    etheraddr_string(ndo, ADDR3)));
	} else if (FC_TO_DS(fc) && !FC_FROM_DS(fc)) {
		ND_PRINT((ndo, "BSSID:%s SA:%s DA:%s ",
		    etheraddr_string(ndo, ADDR1), etheraddr_string(ndo, ADDR2),
		    etheraddr_string(ndo, ADDR3)));
	} else if (FC_TO_DS(fc) && FC_FROM_DS(fc)) {
		ND_PRINT((ndo, "RA:%s TA:%s DA:%s SA:%s ",
		    etheraddr_string(ndo, ADDR1), etheraddr_string(ndo, ADDR2),
		    etheraddr_string(ndo, ADDR3), etheraddr_string(ndo, ADDR4)));
	}

#undef ADDR1
#undef ADDR2
#undef ADDR3
#undef ADDR4
}