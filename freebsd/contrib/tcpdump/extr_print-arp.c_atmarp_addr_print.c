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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  LINKADDR_ATM ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linkaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
atmarp_addr_print(netdissect_options *ndo,
		  const u_char *ha, u_int ha_len, const u_char *srca,
    u_int srca_len)
{
	if (ha_len == 0)
		ND_PRINT((ndo, "<No address>"));
	else {
		ND_PRINT((ndo, "%s", linkaddr_string(ndo, ha, LINKADDR_ATM, ha_len)));
		if (srca_len != 0)
			ND_PRINT((ndo, ",%s",
				  linkaddr_string(ndo, srca, LINKADDR_ATM, srca_len)));
	}
}