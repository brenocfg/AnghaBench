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
struct emitted_diff_symbol {char const* member_0; int member_1; unsigned int member_2; int member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; } ;
struct diff_options {scalar_t__ emitted_symbols; } ;
typedef  enum diff_symbol { ____Placeholder_diff_symbol } diff_symbol ;

/* Variables and functions */
 int /*<<< orphan*/  append_emitted_diff_symbol (struct diff_options*,struct emitted_diff_symbol*) ; 
 int /*<<< orphan*/  emit_diff_symbol_from_struct (struct diff_options*,struct emitted_diff_symbol*) ; 

__attribute__((used)) static void emit_diff_symbol(struct diff_options *o, enum diff_symbol s,
			     const char *line, int len, unsigned flags)
{
	struct emitted_diff_symbol e = {line, len, flags, 0, 0, s};

	if (o->emitted_symbols)
		append_emitted_diff_symbol(o, &e);
	else
		emit_diff_symbol_from_struct(o, &e);
}