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
typedef  int /*<<< orphan*/  xo_xof_flags_t ;
typedef  int /*<<< orphan*/  xo_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  XO_STYLE_ENCODER ; 
 int /*<<< orphan*/ * xo_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ xo_encoder_init (int /*<<< orphan*/ *,char const*) ; 

xo_handle_t *
xo_encoder_create (const char *name, xo_xof_flags_t flags)
{
    xo_handle_t *xop;

    xop = xo_create(XO_STYLE_ENCODER, flags);
    if (xop) {
	if (xo_encoder_init(xop, name)) {
	    xo_destroy(xop);
	    xop = NULL;
	}
    }

    return xop;
}