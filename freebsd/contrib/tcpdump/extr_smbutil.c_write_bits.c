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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 size_t PTR_DIFF (char const*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void
write_bits(netdissect_options *ndo,
           unsigned int val, const char *fmt)
{
    const char *p = fmt;
    int i = 0;

    while ((p = strchr(fmt, '|'))) {
	size_t l = PTR_DIFF(p, fmt);
	if (l && (val & (1 << i)))
	    ND_PRINT((ndo, "%.*s ", (int)l, fmt));
	fmt = p + 1;
	i++;
    }
}