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
typedef  int /*<<< orphan*/  xo_handle_t ;

/* Variables and functions */
 int xo_name_to_style (char const*) ; 
 int /*<<< orphan*/  xo_set_style (int /*<<< orphan*/ *,int) ; 

int
xo_set_style_name (xo_handle_t *xop, const char *name)
{
    if (name == NULL)
	return -1;

    int style = xo_name_to_style(name);

    if (style < 0)
	return -1;

    xo_set_style(xop, style);
    return 0;
}