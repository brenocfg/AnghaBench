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
 int /*<<< orphan*/  UCL_DUPLICATE_APPEND ; 
 int /*<<< orphan*/  UCL_PARSE_UCL ; 
 int ucl_parser_add_chunk_full (struct ucl_parser*,unsigned char const*,size_t,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
ucl_parser_add_chunk_priority (struct ucl_parser *parser,
		const unsigned char *data, size_t len, unsigned priority)
{
	/* We dereference parser, so this check is essential */
	if (parser == NULL) {
		return false;
	}

	return ucl_parser_add_chunk_full (parser, data, len,
				priority, UCL_DUPLICATE_APPEND, UCL_PARSE_UCL);
}