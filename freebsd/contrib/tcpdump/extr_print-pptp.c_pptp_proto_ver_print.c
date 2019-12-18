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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pptp_proto_ver_print(netdissect_options *ndo,
                     const uint16_t *proto_ver)
{
	ND_PRINT((ndo, " PROTO_VER(%u.%u)",	/* Version.Revision */
	       EXTRACT_16BITS(proto_ver) >> 8,
	       EXTRACT_16BITS(proto_ver) & 0xff));
}