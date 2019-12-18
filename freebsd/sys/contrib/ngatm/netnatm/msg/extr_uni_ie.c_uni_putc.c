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
struct unicx {int bufsiz; char* buf; } ;

/* Variables and functions */

__attribute__((used)) static void
uni_putc(int c, struct unicx *cx)
{
	if(cx->bufsiz > 1) {
		*cx->buf++ = c;
		cx->bufsiz--;
		*cx->buf = '\0';
	}
}