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
typedef  int /*<<< orphan*/  MD2_INT ;

/* Variables and functions */

const char *MD2_options(void)
{
    if (sizeof(MD2_INT) == 1)
        return "md2(char)";
    else
        return "md2(int)";
}