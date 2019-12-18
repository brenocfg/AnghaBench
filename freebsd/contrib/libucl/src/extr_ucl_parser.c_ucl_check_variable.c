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
struct ucl_parser {int dummy; } ;

/* Variables and functions */
 char* ucl_check_variable_safe (struct ucl_parser*,char const*,size_t,size_t*,int,int*) ; 

__attribute__((used)) static const char *
ucl_check_variable (struct ucl_parser *parser, const char *ptr,
		size_t remain, size_t *out_len, bool *vars_found)
{
	const char *p, *end, *ret = ptr;
	bool found = false;

	if (*ptr == '{') {
		/* We need to match the variable enclosed in braces */
		p = ptr + 1;
		end = ptr + remain;
		while (p < end) {
			if (*p == '}') {
				ret = ucl_check_variable_safe (parser, ptr + 1, p - ptr - 1,
						out_len, true, &found);
				if (found) {
					/* {} must be excluded actually */
					ret ++;
					if (!*vars_found) {
						*vars_found = true;
					}
				}
				else {
					*out_len += 2;
				}
				break;
			}
			p ++;
		}
	}
	else if (*ptr != '$') {
		/* Not count escaped dollar sign */
		ret = ucl_check_variable_safe (parser, ptr, remain, out_len, false, &found);
		if (found && !*vars_found) {
			*vars_found = true;
		}
		if (!found) {
			(*out_len) ++;
		}
	}
	else {
		ret ++;
		(*out_len) ++;
	}

	return ret;
}