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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  safeputchar (int /*<<< orphan*/ *,unsigned char const) ; 

__attribute__((used)) static void
print_asc(netdissect_options *ndo,
          const unsigned char *buf, int len)
{
    int i;
    for (i = 0; i < len; i++)
        safeputchar(ndo, buf[i]);
}