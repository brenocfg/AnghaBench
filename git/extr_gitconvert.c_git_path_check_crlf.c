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
typedef  enum crlf_action { ____Placeholder_crlf_action } crlf_action ;

/* Variables and functions */
 scalar_t__ ATTR_FALSE (char const*) ; 
 scalar_t__ ATTR_TRUE (char const*) ; 
 scalar_t__ ATTR_UNSET (char const*) ; 
 int CRLF_AUTO ; 
 int CRLF_BINARY ; 
 int CRLF_TEXT ; 
 int CRLF_TEXT_INPUT ; 
 int CRLF_UNDEFINED ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum crlf_action git_path_check_crlf(struct attr_check_item *check)
{
	const char *value = check->value;

	if (ATTR_TRUE(value))
		return CRLF_TEXT;
	else if (ATTR_FALSE(value))
		return CRLF_BINARY;
	else if (ATTR_UNSET(value))
		;
	else if (!strcmp(value, "input"))
		return CRLF_TEXT_INPUT;
	else if (!strcmp(value, "auto"))
		return CRLF_AUTO;
	return CRLF_UNDEFINED;
}