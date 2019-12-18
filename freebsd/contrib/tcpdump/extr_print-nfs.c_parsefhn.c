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
 int /*<<< orphan*/ * parsefh (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* parsefn (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static const uint32_t *
parsefhn(netdissect_options *ndo,
         register const uint32_t *dp, int v3)
{
	dp = parsefh(ndo, dp, v3);
	if (dp == NULL)
		return (NULL);
	ND_PRINT((ndo, " "));
	return (parsefn(ndo, dp));
}