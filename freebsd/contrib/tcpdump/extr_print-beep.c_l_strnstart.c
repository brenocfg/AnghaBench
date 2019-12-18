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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_TTEST2 (char const,scalar_t__) ; 
 scalar_t__ strncmp (char const*,char const*,scalar_t__) ; 

__attribute__((used)) static int
l_strnstart(netdissect_options *ndo, const char *tstr1, u_int tl1,
    const char *str2, u_int l2)
{
	if (!ND_TTEST2(*str2, tl1)) {
		/*
		 * We don't have tl1 bytes worth of captured data
		 * for the string, so we can't check for this
		 * string.
		 */
		return 0;
	}
	if (tl1 > l2)
		return 0;

	return (strncmp(tstr1, str2, tl1) == 0 ? 1 : 0);
}