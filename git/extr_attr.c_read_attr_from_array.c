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
struct attr_stack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_attr_line (struct attr_stack*,char const*,char*,int,int) ; 
 struct attr_stack* xcalloc (int,int) ; 

__attribute__((used)) static struct attr_stack *read_attr_from_array(const char **list)
{
	struct attr_stack *res;
	const char *line;
	int lineno = 0;

	res = xcalloc(1, sizeof(*res));
	while ((line = *(list++)) != NULL)
		handle_attr_line(res, line, "[builtin]", ++lineno, 1);
	return res;
}