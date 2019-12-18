#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* rule_name; unsigned int rule_bits; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int WS_DEFAULT_RULE ; 
 unsigned int WS_INDENT_WITH_NON_TAB ; 
 unsigned int WS_TAB_IN_INDENT ; 
 unsigned int WS_TAB_WIDTH_MASK ; 
 unsigned int atoi (char const*) ; 
 int /*<<< orphan*/  die (char*) ; 
 char* strchrnul (char const*,char) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int strspn (char const*,char*) ; 
 int /*<<< orphan*/  warning (char*,int,char const*) ; 
 TYPE_1__* whitespace_rule_names ; 

unsigned parse_whitespace_rule(const char *string)
{
	unsigned rule = WS_DEFAULT_RULE;

	while (string) {
		int i;
		size_t len;
		const char *ep;
		int negated = 0;

		string = string + strspn(string, ", \t\n\r");
		ep = strchrnul(string, ',');
		len = ep - string;

		if (*string == '-') {
			negated = 1;
			string++;
			len--;
		}
		if (!len)
			break;
		for (i = 0; i < ARRAY_SIZE(whitespace_rule_names); i++) {
			if (strncmp(whitespace_rule_names[i].rule_name,
				    string, len))
				continue;
			if (negated)
				rule &= ~whitespace_rule_names[i].rule_bits;
			else
				rule |= whitespace_rule_names[i].rule_bits;
			break;
		}
		if (strncmp(string, "tabwidth=", 9) == 0) {
			unsigned tabwidth = atoi(string + 9);
			if (0 < tabwidth && tabwidth < 0100) {
				rule &= ~WS_TAB_WIDTH_MASK;
				rule |= tabwidth;
			}
			else
				warning("tabwidth %.*s out of range",
					(int)(len - 9), string + 9);
		}
		string = ep;
	}

	if (rule & WS_TAB_IN_INDENT && rule & WS_INDENT_WITH_NON_TAB)
		die("cannot enforce both tab-in-indent and indent-with-non-tab");
	return rule;
}