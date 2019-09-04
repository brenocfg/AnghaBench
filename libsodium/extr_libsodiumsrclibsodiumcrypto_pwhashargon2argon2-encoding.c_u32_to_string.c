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
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  U32_STR_MAXSIZE ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void
u32_to_string(char *str, uint32_t x)
{
    char   tmp[U32_STR_MAXSIZE - 1U];
    size_t i;

    i = sizeof tmp;
    do {
        tmp[--i] = (x % (uint32_t) 10U) + '0';
        x /= (uint32_t) 10U;
    } while (x != 0U && i != 0U);
    memcpy(str, &tmp[i], (sizeof tmp) - i);
    str[(sizeof tmp) - i] = 0;
}