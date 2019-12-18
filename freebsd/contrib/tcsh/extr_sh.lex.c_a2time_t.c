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
typedef  int time_t ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (unsigned char) ; 

__attribute__((used)) static time_t
a2time_t(Char *wordx)
{
    /* Attempt to distinguish timestamps from other possible entries.
     * Format: "+NNNNNNNNNN" (10 digits, left padded with ascii '0') */

    time_t ret;
    Char *s;
    int ct;

    if (!wordx || *(s = wordx) != '+')
	return (time_t)0;

    for (++s, ret = 0, ct = 0; *s; ++s, ++ct) {
	if (!isdigit((unsigned char)*s))
	    return (time_t)0;
	ret = ret * 10 + (time_t)((unsigned char)*s - '0');
    }

    if (ct != 10)
	return (time_t)0;

    return ret;
}