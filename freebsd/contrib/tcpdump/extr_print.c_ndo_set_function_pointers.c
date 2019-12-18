#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ndo_warning; int /*<<< orphan*/  ndo_error; int /*<<< orphan*/  ndo_printf; int /*<<< orphan*/  ndo_default_print; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ndo_default_print ; 
 int /*<<< orphan*/  ndo_error ; 
 int /*<<< orphan*/  ndo_printf ; 
 int /*<<< orphan*/  ndo_warning ; 

void
ndo_set_function_pointers(netdissect_options *ndo)
{
	ndo->ndo_default_print=ndo_default_print;
	ndo->ndo_printf=ndo_printf;
	ndo->ndo_error=ndo_error;
	ndo->ndo_warning=ndo_warning;
}