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
typedef  int /*<<< orphan*/  xo_ssize_t ;
typedef  int /*<<< orphan*/  xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XSS_CLOSE_INSTANCE ; 
 int /*<<< orphan*/  xo_transition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

xo_ssize_t
xo_close_instance_h (xo_handle_t *xop, const char *name)
{
    return xo_transition(xop, 0, name, XSS_CLOSE_INSTANCE);
}