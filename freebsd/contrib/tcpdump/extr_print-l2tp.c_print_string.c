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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_string(netdissect_options *ndo, const u_char *dat, u_int length)
{
	u_int i;
	for (i=0; i<length; i++) {
		ND_PRINT((ndo, "%c", *dat++));
	}
}