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
typedef  int u_int ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l2tp_proto_ver_print(netdissect_options *ndo, const uint16_t *dat, u_int length)
{
	if (length < 2) {
		ND_PRINT((ndo, "AVP too short"));
		return;
	}
	ND_PRINT((ndo, "%u.%u", (EXTRACT_16BITS(dat) >> 8),
	    (EXTRACT_16BITS(dat) & 0xff)));
}