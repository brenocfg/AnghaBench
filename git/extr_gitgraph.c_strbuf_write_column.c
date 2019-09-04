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
struct strbuf {int dummy; } ;
struct column {scalar_t__ color; } ;

/* Variables and functions */
 scalar_t__ column_colors_max ; 
 int /*<<< orphan*/  column_get_color_code (scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void strbuf_write_column(struct strbuf *sb, const struct column *c,
				char col_char)
{
	if (c->color < column_colors_max)
		strbuf_addstr(sb, column_get_color_code(c->color));
	strbuf_addch(sb, col_char);
	if (c->color < column_colors_max)
		strbuf_addstr(sb, column_get_color_code(column_colors_max));
}