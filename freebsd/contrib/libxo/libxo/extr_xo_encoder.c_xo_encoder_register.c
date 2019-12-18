#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  xe_handler; } ;
typedef  TYPE_1__ xo_encoder_node_t ;
typedef  int /*<<< orphan*/  xo_encoder_func_t ;

/* Variables and functions */
 TYPE_1__* xo_encoder_find (char const*) ; 
 TYPE_1__* xo_encoder_list_add (char const*) ; 
 int /*<<< orphan*/  xo_encoder_setup () ; 

void
xo_encoder_register (const char *name, xo_encoder_func_t func)
{
    xo_encoder_setup();

    xo_encoder_node_t *xep = xo_encoder_find(name);

    if (xep)			/* "We alla-ready got one" */
	return;

    xep = xo_encoder_list_add(name);
    if (xep)
	xep->xe_handler = func;
}