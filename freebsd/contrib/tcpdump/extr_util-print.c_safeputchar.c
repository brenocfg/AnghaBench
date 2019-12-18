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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ ND_ISPRINT (int const) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

void
safeputchar(netdissect_options *ndo,
            const u_char c)
{
	ND_PRINT((ndo, (c < 0x80 && ND_ISPRINT(c)) ? "%c" : "\\0x%02x", c));
}