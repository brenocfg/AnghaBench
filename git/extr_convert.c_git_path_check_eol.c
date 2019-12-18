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
struct attr_check_item {char* value; } ;
typedef  enum eol { ____Placeholder_eol } eol ;

/* Variables and functions */
 scalar_t__ ATTR_UNSET (char const*) ; 
 int EOL_CRLF ; 
 int EOL_LF ; 
 int EOL_UNSET ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum eol git_path_check_eol(struct attr_check_item *check)
{
	const char *value = check->value;

	if (ATTR_UNSET(value))
		;
	else if (!strcmp(value, "lf"))
		return EOL_LF;
	else if (!strcmp(value, "crlf"))
		return EOL_CRLF;
	return EOL_UNSET;
}