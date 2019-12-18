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
struct match_attr {int dummy; } ;
struct attr_stack {scalar_t__ num_matches; struct match_attr** attrs; int /*<<< orphan*/  alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct match_attr**,scalar_t__,int /*<<< orphan*/ ) ; 
 struct match_attr* parse_attr_line (char const*,char const*,int,int) ; 

__attribute__((used)) static void handle_attr_line(struct attr_stack *res,
			     const char *line,
			     const char *src,
			     int lineno,
			     int macro_ok)
{
	struct match_attr *a;

	a = parse_attr_line(line, src, lineno, macro_ok);
	if (!a)
		return;
	ALLOC_GROW(res->attrs, res->num_matches + 1, res->alloc);
	res->attrs[res->num_matches++] = a;
}