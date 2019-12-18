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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 short EXTRACT_16BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const u_char *
print_sl_winchange(netdissect_options *ndo,
                   register const u_char *cp)
{
	register short i;

	if ((i = *cp++) == 0) {
		i = EXTRACT_16BITS(cp);
		cp += 2;
	}
	if (i >= 0)
		ND_PRINT((ndo, " W+%d", i));
	else
		ND_PRINT((ndo, " W%d", i));
	return (cp);
}