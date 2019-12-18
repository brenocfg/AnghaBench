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
typedef  int ptrdiff_t ;
typedef  scalar_t__ UWORD ;
typedef  scalar_t__ UINT8 ;

/* Variables and functions */

__attribute__((used)) static void zero_pad(UINT8 *p, int nbytes)
{
/* Write "nbytes" of zeroes, beginning at "p" */
    if (nbytes >= (int)sizeof(UWORD)) {
        while ((ptrdiff_t)p % sizeof(UWORD)) {
            *p = 0;
            nbytes--;
            p++;
        }
        while (nbytes >= (int)sizeof(UWORD)) {
            *(UWORD *)p = 0;
            nbytes -= sizeof(UWORD);
            p += sizeof(UWORD);
        }
    }
    while (nbytes) {
        *p = 0;
        nbytes--;
        p++;
    }
}