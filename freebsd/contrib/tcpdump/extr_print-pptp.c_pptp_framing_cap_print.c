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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int PPTP_FRAMING_CAP_ASYNC_MASK ; 
 int PPTP_FRAMING_CAP_SYNC_MASK ; 

__attribute__((used)) static void
pptp_framing_cap_print(netdissect_options *ndo,
                       const uint32_t *framing_cap)
{
	ND_PRINT((ndo, " FRAME_CAP("));
	if (EXTRACT_32BITS(framing_cap) & PPTP_FRAMING_CAP_ASYNC_MASK) {
                ND_PRINT((ndo, "A"));		/* Async */
        }
        if (EXTRACT_32BITS(framing_cap) & PPTP_FRAMING_CAP_SYNC_MASK) {
                ND_PRINT((ndo, "S"));		/* Sync */
        }
	ND_PRINT((ndo, ")"));
}