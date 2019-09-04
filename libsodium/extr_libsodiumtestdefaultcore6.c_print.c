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
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
print(unsigned char *x, unsigned char *y)
{
    int          i;
    unsigned int borrow = 0;

    for (i = 0; i < 4; ++i) {
        unsigned int xi = x[i];
        unsigned int yi = y[i];
        printf(",0x%02x", 255 & (xi - yi - borrow));
        borrow = (xi < yi + borrow);
    }
}