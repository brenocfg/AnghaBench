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
 int /*<<< orphan*/  xo_default_handle ; 
 int /*<<< orphan*/  xo_default_init () ; 
 scalar_t__ xo_default_inited ; 

__attribute__((used)) static xo_handle_t *
xo_default (xo_handle_t *xop)
{
    if (xop == NULL) {
	if (xo_default_inited == 0)
	    xo_default_init();
	xop = &xo_default_handle;
    }

    return xop;
}