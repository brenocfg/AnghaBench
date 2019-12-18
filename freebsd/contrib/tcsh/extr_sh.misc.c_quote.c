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
typedef  char Char ;

/* Variables and functions */
 char QUOTE ; 

Char   *
quote(Char *cp)
{
    Char *dp = cp;

    if (!cp)
	return (cp);
    while (*dp != '\0') {
#ifdef WIDE_STRINGS
	if ((*dp & 0xffffff80) == 0)	/* *dp < 0x80 */
#elif defined SHORT_STRINGS
	if ((*dp & 0xff80) == 0)	/* *dp < 0x80 */
#else
	if ((*dp & 0x80) == 0)		/* *dp < 0x80 */
#endif
	    *dp |= QUOTE;
	dp++;
    }
    return (cp);
}