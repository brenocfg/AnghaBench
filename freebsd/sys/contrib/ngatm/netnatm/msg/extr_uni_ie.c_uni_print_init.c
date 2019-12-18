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
struct unicx {int tabsiz; char* buf; size_t bufsiz; scalar_t__ doindent; scalar_t__ nprefix; scalar_t__ indent; scalar_t__ dont_init; } ;

/* Variables and functions */

void
uni_print_init(char *buf, size_t bufsiz, struct unicx *cx)
{
	if (cx->dont_init)
		return;

	cx->indent = 0;
	cx->nprefix = 0;
	cx->doindent = 0;
	if (cx->tabsiz == 0)
		cx->tabsiz = 4;
	cx->buf = buf;
	cx->bufsiz = bufsiz;
}