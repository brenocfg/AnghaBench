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
struct attr_check {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {char* value; int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 scalar_t__ ATTR_FALSE (char const*) ; 
 scalar_t__ ATTR_TRUE (char const*) ; 
 scalar_t__ ATTR_UNSET (char const*) ; 
 char* git_attr_name (int /*<<< orphan*/ ) ; 
 scalar_t__ nul_term_line ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,...) ; 
 int /*<<< orphan*/  quote_c_style (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void output_attr(struct attr_check *check, const char *file)
{
	int j;
	int cnt = check->nr;

	for (j = 0; j < cnt; j++) {
		const char *value = check->items[j].value;

		if (ATTR_TRUE(value))
			value = "set";
		else if (ATTR_FALSE(value))
			value = "unset";
		else if (ATTR_UNSET(value))
			value = "unspecified";

		if (nul_term_line) {
			printf("%s%c" /* path */
			       "%s%c" /* attrname */
			       "%s%c" /* attrvalue */,
			       file, 0,
			       git_attr_name(check->items[j].attr), 0, value, 0);
		} else {
			quote_c_style(file, NULL, stdout, 0);
			printf(": %s: %s\n",
			       git_attr_name(check->items[j].attr), value);
		}
	}
}