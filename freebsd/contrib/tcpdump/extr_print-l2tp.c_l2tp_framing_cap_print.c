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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int L2TP_FRAMING_CAP_ASYNC_MASK ; 
 int L2TP_FRAMING_CAP_SYNC_MASK ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2tp_framing_cap_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	const uint32_t *ptr = (const uint32_t *)dat;

	if (length < 4) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	if (EXTRACT_32BITS(ptr) &  L2TP_FRAMING_CAP_ASYNC_MASK) {
		ND_PRINT((ndo, "A"));
	}
	if (EXTRACT_32BITS(ptr) &  L2TP_FRAMING_CAP_SYNC_MASK) {
		ND_PRINT((ndo, "S"));
	}
}