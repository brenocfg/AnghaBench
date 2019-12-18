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
struct unicx {int doindent; scalar_t__ multiline; } ;

/* Variables and functions */
 int /*<<< orphan*/  uni_putc (char,struct unicx*) ; 

void
uni_print_eol(struct unicx *cx)
{
	if (cx->multiline) {
		if (!cx->doindent) {
			uni_putc('\n', cx);
			cx->doindent = 1;
		}
	} 
}