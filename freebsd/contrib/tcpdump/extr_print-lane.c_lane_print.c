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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct lane_controlhdr {int /*<<< orphan*/  lec_opcode; int /*<<< orphan*/  lec_vers; int /*<<< orphan*/  lec_proto; int /*<<< orphan*/  lec_header; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lane_hdr_print ; 
 int /*<<< orphan*/  lecop2str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

void
lane_print(netdissect_options *ndo, const u_char *p, u_int length, u_int caplen)
{
	const struct lane_controlhdr *lec;

	if (caplen < sizeof(struct lane_controlhdr)) {
		ND_PRINT((ndo, "[|lane]"));
		return;
	}

	lec = (const struct lane_controlhdr *)p;
	if (EXTRACT_16BITS(&lec->lec_header) == 0xff00) {
		/*
		 * LE Control.
		 */
		ND_PRINT((ndo, "lec: proto %x vers %x %s",
		    lec->lec_proto, lec->lec_vers,
		    tok2str(lecop2str, "opcode-#%u", EXTRACT_16BITS(&lec->lec_opcode))));
		return;
	}

	/*
	 * Go past the LE header.
	 */
	length -= 2;
	caplen -= 2;
	p += 2;

	/*
	 * Now print the encapsulated frame, under the assumption
	 * that it's an Ethernet frame.
	 */
	ether_print(ndo, p, length, caplen, lane_hdr_print, p - 2);
}