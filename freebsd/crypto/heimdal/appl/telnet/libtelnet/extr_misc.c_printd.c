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
 int /*<<< orphan*/  printf (char*,unsigned char const) ; 

void
printd(const unsigned char *data, int cnt)
{
    if (cnt > 16)
	cnt = 16;
    while (cnt-- > 0) {
	printf(" %02x", *data);
	++data;
    }
}