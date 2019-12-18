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
 unsigned char NUL ; 
 int* charmap ; 

int
strneqvcmp(char const * s1, char const * s2, int ct)
{
    for (; ct > 0; --ct) {
        unsigned char u1 = (unsigned char) *s1++;
        unsigned char u2 = (unsigned char) *s2++;
        int dif;
        if (u1 == u2) {
            if (u1 == NUL)
                return 0;
            continue;
        }

        dif = charmap[ u1 ] - charmap[ u2 ];

        if (dif != 0)
            return dif;

        if (u1 == NUL)
            return 0;
    }

    return 0;
}