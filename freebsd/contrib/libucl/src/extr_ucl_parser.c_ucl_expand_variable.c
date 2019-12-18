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
struct ucl_parser {int flags; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned char* UCL_ALLOC (size_t) ; 
 int UCL_PARSER_DISABLE_MACRO ; 
 char* ucl_check_variable (struct ucl_parser*,char const*,int,size_t*,int*) ; 
 char* ucl_expand_single_variable (struct ucl_parser*,char const*,int,unsigned char**) ; 

__attribute__((used)) static ssize_t
ucl_expand_variable (struct ucl_parser *parser, unsigned char **dst,
		const char *src, size_t in_len)
{
	const char *p, *end = src + in_len;
	unsigned char *d;
	size_t out_len = 0;
	bool vars_found = false;

	if (parser->flags & UCL_PARSER_DISABLE_MACRO) {
		*dst = NULL;
		return in_len;
	}

	p = src;
	while (p != end) {
		if (*p == '$') {
			p = ucl_check_variable (parser, p + 1, end - p - 1, &out_len, &vars_found);
		}
		else {
			p ++;
			out_len ++;
		}
	}

	if (!vars_found) {
		/* Trivial case */
		*dst = NULL;
		return in_len;
	}

	*dst = UCL_ALLOC (out_len + 1);
	if (*dst == NULL) {
		return in_len;
	}

	d = *dst;
	p = src;
	while (p != end) {
		if (*p == '$') {
			p = ucl_expand_single_variable (parser, p, end - p, &d);
		}
		else {
			*d++ = *p++;
		}
	}

	*d = '\0';

	return out_len;
}