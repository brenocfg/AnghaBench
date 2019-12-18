#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  xo_encoder; int /*<<< orphan*/  xo_style; } ;
typedef  TYPE_1__ xo_handle_t ;
typedef  int /*<<< orphan*/  xo_encoder_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  XO_STYLE_ENCODER ; 
 TYPE_1__* xo_default (TYPE_1__*) ; 

void
xo_set_encoder (xo_handle_t *xop, xo_encoder_func_t encoder)
{
    xop = xo_default(xop);

    xop->xo_style = XO_STYLE_ENCODER;
    xop->xo_encoder = encoder;
}