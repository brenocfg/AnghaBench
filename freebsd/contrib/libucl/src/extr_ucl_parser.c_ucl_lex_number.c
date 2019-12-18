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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_parser {int flags; int /*<<< orphan*/  err; } ;
struct ucl_chunk {unsigned char const* pos; int /*<<< orphan*/  column; int /*<<< orphan*/  remain; int /*<<< orphan*/  end; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  UCL_ESYNTAX ; 
 int UCL_PARSER_NO_TIME ; 
 int ucl_maybe_parse_number (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ,char const**,int,int,int) ; 
 int /*<<< orphan*/  ucl_set_err (struct ucl_parser*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
ucl_lex_number (struct ucl_parser *parser,
		struct ucl_chunk *chunk, ucl_object_t *obj)
{
	const unsigned char *pos;
	int ret;

	ret = ucl_maybe_parse_number (obj, chunk->pos, chunk->end, (const char **)&pos,
			true, false, ((parser->flags & UCL_PARSER_NO_TIME) == 0));

	if (ret == 0) {
		chunk->remain -= pos - chunk->pos;
		chunk->column += pos - chunk->pos;
		chunk->pos = pos;
		return true;
	}
	else if (ret == ERANGE) {
		ucl_set_err (parser, UCL_ESYNTAX, "numeric value out of range",
				&parser->err);
	}

	return false;
}