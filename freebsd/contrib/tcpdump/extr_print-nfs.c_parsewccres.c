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
 int /*<<< orphan*/ * parse_wcc_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * parsestatus (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static int
parsewccres(netdissect_options *ndo,
            const uint32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(ndo, dp, &er)))
		return (0);
	return parse_wcc_data(ndo, dp, verbose) != NULL;
}