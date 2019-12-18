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

/* Variables and functions */
 int WRDE_BADCHAR ; 
 int WRDE_SYNTAX ; 

__attribute__((used)) static int
we_check(const char *words)
{
	char c;
	/* Saw \ or $, possibly not special: */
	bool quote = false, dollar = false;
	/* Saw ', ", ${, ` or $(, possibly not special: */
	bool have_sq = false, have_dq = false, have_par_begin = false;
	bool have_cmd = false;
	/* Definitely saw a ', ", ${, ` or $(, need a closing character: */
	bool need_sq = false, need_dq = false, need_par_end = false;
	bool need_cmd_old = false, need_cmd_new = false;

	while ((c = *words++) != '\0') {
		switch (c) {
		case '\\':
			quote = !quote;
			continue;
		case '$':
			if (quote)
				quote = false;
			else
				dollar = !dollar;
			continue;
		case '\'':
			if (!quote && !have_sq && !have_dq)
				need_sq = true;
			else
				need_sq = false;
			have_sq = true;
			break;
		case '"':
			if (!quote && !have_sq && !have_dq)
				need_dq = true;
			else
				need_dq = false;
			have_dq = true;
			break;
		case '`':
			if (!quote && !have_sq && !have_cmd)
				need_cmd_old = true;
			else
				need_cmd_old = false;
			have_cmd = true;
			break;
		case '{':
			if (!quote && !dollar && !have_sq && !have_dq &&
			    !have_cmd)
				return (WRDE_BADCHAR);
			if (dollar) {
				if (!quote && !have_sq)
					need_par_end = true;
				have_par_begin = true;
			}
			break;
		case '}':
			if (!quote && !have_sq && !have_dq && !have_par_begin &&
			    !have_cmd)
				return (WRDE_BADCHAR);
			need_par_end = false;
			break;
		case '(':
			if (!quote && !dollar && !have_sq && !have_dq &&
			    !have_cmd)
				return (WRDE_BADCHAR);
			if (dollar) {
				if (!quote && !have_sq)
					need_cmd_new = true;
				have_cmd = true;
			}
			break;
		case ')':
			if (!quote && !have_sq && !have_dq && !have_cmd)
				return (WRDE_BADCHAR);
			need_cmd_new = false;
			break;
		case '|': case '&': case ';': case '<': case '>': case '\n':
			if (!quote && !have_sq && !have_dq && !have_cmd)
				return (WRDE_BADCHAR);
			break;
		default:
			break;
		}
		quote = dollar = false;
	}
	if (quote || dollar || need_sq || need_dq || need_par_end ||
	    need_cmd_old || need_cmd_new)
		return (WRDE_SYNTAX);

	return (0);
}