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
struct unicx {scalar_t__ nprefix; char const** prefix; } ;

/* Variables and functions */
 scalar_t__ PRINT_NPREFIX ; 

void
uni_print_push_prefix(const char *prefix, struct unicx *cx)
{
	if (cx->nprefix < PRINT_NPREFIX)
		cx->prefix[cx->nprefix++] = prefix;
}