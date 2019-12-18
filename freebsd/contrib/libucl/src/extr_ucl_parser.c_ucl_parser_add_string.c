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
struct ucl_parser {int /*<<< orphan*/  default_priority; } ;

/* Variables and functions */
 int ucl_parser_add_string_priority (struct ucl_parser*,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 

bool
ucl_parser_add_string (struct ucl_parser *parser, const char *data,
		size_t len)
{
	if (parser == NULL) {
		return false;
	}

	return ucl_parser_add_string_priority (parser,
			(const unsigned char *)data, len, parser->default_priority);
}