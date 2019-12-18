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

/* Variables and functions */
 int /*<<< orphan*/  reverse (char*,char*) ; 

__attribute__((used)) static int
uitoa(unsigned n, char* s)
{
    char* ss = s;
    do {
        *ss++ = '0' + n % 10;
    } while (n /= 10);
    reverse(s, ss);
    return ss - s;
}