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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
of_header_print(netdissect_options *ndo, const uint8_t version, const uint8_t type,
                      const uint16_t length, const uint32_t xid)
{
	ND_PRINT((ndo, "\n\tversion unknown (0x%02x), type 0x%02x, length %u, xid 0x%08x",
	       version, type, length, xid));
}