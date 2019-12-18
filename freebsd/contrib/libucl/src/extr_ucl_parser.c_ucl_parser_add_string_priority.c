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
struct ucl_parser {int /*<<< orphan*/  err; } ;

/* Variables and functions */
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*) ; 
 int ucl_parser_add_chunk_priority (struct ucl_parser*,unsigned char const*,size_t,unsigned int) ; 

bool
ucl_parser_add_string_priority (struct ucl_parser *parser, const char *data,
		size_t len, unsigned priority)
{
	if (data == NULL) {
		ucl_create_err (&parser->err, "invalid string added");
		return false;
	}
	if (len == 0) {
		len = strlen (data);
	}

	return ucl_parser_add_chunk_priority (parser,
			(const unsigned char *)data, len, priority);
}