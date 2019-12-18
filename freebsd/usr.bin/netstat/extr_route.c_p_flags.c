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
struct bits {int b_mask; int /*<<< orphan*/  b_name; } ;

/* Variables and functions */
 struct bits* bits ; 
 int /*<<< orphan*/  fmt_flags (int) ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

__attribute__((used)) static void
p_flags(int f, const char *format)
{
	struct bits *p;

	xo_emit(format, fmt_flags(f));

	xo_open_list("flags_pretty");
	for (p = bits; p->b_mask; p++)
		if (p->b_mask & f)
			xo_emit("{le:flags_pretty/%s}", p->b_name);
	xo_close_list("flags_pretty");
}