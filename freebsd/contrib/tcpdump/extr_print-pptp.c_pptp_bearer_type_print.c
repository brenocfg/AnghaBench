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
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pptp_btype_str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pptp_bearer_type_print(netdissect_options *ndo,
                       const uint32_t *bearer_type)
{
	ND_PRINT((ndo, " BEARER_TYPE(%s)",
	          tok2str(pptp_btype_str, "?", EXTRACT_32BITS(bearer_type))));
}