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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2tp_accm_print(netdissect_options *ndo, const u_char *dat, u_int length)
{
	const uint16_t *ptr = (const uint16_t *)dat;
	uint16_t val_h, val_l;

	if (length < 2) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	ptr++;		/* skip "Reserved" */
	length -= 2;

	if (length < 4) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	val_h = EXTRACT_16BITS(ptr); ptr++; length -= 2;
	val_l = EXTRACT_16BITS(ptr); ptr++; length -= 2;
	ND_PRINT((ndo, "send=%08x ", (val_h<<16) + val_l));

	if (length < 4) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	val_h = EXTRACT_16BITS(ptr); ptr++;
	val_l = EXTRACT_16BITS(ptr); ptr++;
	ND_PRINT((ndo, "recv=%08x ", (val_h<<16) + val_l));
}