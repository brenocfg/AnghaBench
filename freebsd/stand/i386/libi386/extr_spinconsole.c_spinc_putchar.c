#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* c_out ) (char) ;} ;

/* Variables and functions */
 TYPE_1__* parent ; 
 int /*<<< orphan*/  stub1 (char) ; 
 int /*<<< orphan*/  stub2 (char) ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spinc_putchar(int c)
{
	static unsigned tw_chars = 0x5C2D2F7C;    /* "\-/|" */
	static time_t lasttime = 0;
	time_t now;

	now = time(0);
	if (now < (lasttime + 1))
		return;
#ifdef TERM_EMU
	if (lasttime > 0)
		parent->c_out('\b');
#endif
	lasttime = now;
	parent->c_out((char)tw_chars);
	tw_chars = (tw_chars >> 8) | ((tw_chars & (unsigned long)0xFF) << 24);
}