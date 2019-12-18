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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int GEONET_ADDR_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  linkaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
print_long_pos_vector(netdissect_options *ndo,
                      const u_char *bp)
{
	uint32_t lat, lon;

	if (!ND_TTEST2(*bp, GEONET_ADDR_LEN))
		return (-1);
	ND_PRINT((ndo, "GN_ADDR:%s ", linkaddr_string (ndo, bp, 0, GEONET_ADDR_LEN)));

	if (!ND_TTEST2(*(bp+12), 8))
		return (-1);
	lat = EXTRACT_32BITS(bp+12);
	ND_PRINT((ndo, "lat:%d ", lat));
	lon = EXTRACT_32BITS(bp+16);
	ND_PRINT((ndo, "lon:%d", lon));
	return (0);
}