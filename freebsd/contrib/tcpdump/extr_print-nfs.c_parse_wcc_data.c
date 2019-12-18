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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* parse_post_op_attr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * parse_pre_op_attr (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const uint32_t *
parse_wcc_data(netdissect_options *ndo,
               const uint32_t *dp, int verbose)
{
	if (verbose > 1)
		ND_PRINT((ndo, " PRE:"));
	if (!(dp = parse_pre_op_attr(ndo, dp, verbose)))
		return (0);

	if (verbose)
		ND_PRINT((ndo, " POST:"));
	return parse_post_op_attr(ndo, dp, verbose);
}