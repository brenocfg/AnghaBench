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
struct ucl_parser {scalar_t__ state; scalar_t__ recursion; int /*<<< orphan*/  err; int /*<<< orphan*/ * top_obj; int /*<<< orphan*/  chunks; } ;
struct ucl_chunk {unsigned char const* begin; size_t remain; unsigned char const* pos; unsigned char const* end; int line; unsigned int priority; int strategy; int parse_type; scalar_t__ column; } ;
typedef  enum ucl_parse_type { ____Placeholder_ucl_parse_type } ucl_parse_type ;
typedef  enum ucl_duplicate_strategy { ____Placeholder_ucl_duplicate_strategy } ucl_duplicate_strategy ;

/* Variables and functions */
 int /*<<< orphan*/  LL_PREPEND (int /*<<< orphan*/ ,struct ucl_chunk*) ; 
 struct ucl_chunk* UCL_ALLOC (int) ; 
 scalar_t__ UCL_MAX_RECURSION ; 
 int /*<<< orphan*/  UCL_OBJECT ; 
 int UCL_PARSE_AUTO ; 
#define  UCL_PARSE_CSEXP 130 
#define  UCL_PARSE_MSGPACK 129 
#define  UCL_PARSE_UCL 128 
 scalar_t__ UCL_STATE_ERROR ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * ucl_object_new_full (int /*<<< orphan*/ ,unsigned int) ; 
 int ucl_parse_csexp (struct ucl_parser*) ; 
 int ucl_parse_msgpack (struct ucl_parser*) ; 
 int ucl_state_machine (struct ucl_parser*) ; 

bool
ucl_parser_add_chunk_full (struct ucl_parser *parser, const unsigned char *data,
		size_t len, unsigned priority, enum ucl_duplicate_strategy strat,
		enum ucl_parse_type parse_type)
{
	struct ucl_chunk *chunk;

	if (parser == NULL) {
		return false;
	}

	if (data == NULL && len != 0) {
		ucl_create_err (&parser->err, "invalid chunk added");
		return false;
	}

	if (parser->state != UCL_STATE_ERROR) {
		chunk = UCL_ALLOC (sizeof (struct ucl_chunk));
		if (chunk == NULL) {
			ucl_create_err (&parser->err, "cannot allocate chunk structure");
			return false;
		}

		if (parse_type == UCL_PARSE_AUTO && len > 0) {
			/* We need to detect parse type by the first symbol */
			if ((*data & 0x80) == 0x80 && (*data >= 0xdc && *data <= 0xdf)) {
				parse_type = UCL_PARSE_MSGPACK;
			}
			else if (*data == '(') {
				parse_type = UCL_PARSE_CSEXP;
			}
			else {
				parse_type = UCL_PARSE_UCL;
			}
		}

		chunk->begin = data;
		chunk->remain = len;
		chunk->pos = chunk->begin;
		chunk->end = chunk->begin + len;
		chunk->line = 1;
		chunk->column = 0;
		chunk->priority = priority;
		chunk->strategy = strat;
		chunk->parse_type = parse_type;
		LL_PREPEND (parser->chunks, chunk);
		parser->recursion ++;

		if (parser->recursion > UCL_MAX_RECURSION) {
			ucl_create_err (&parser->err, "maximum include nesting limit is reached: %d",
					parser->recursion);
			return false;
		}

		if (len > 0) {
			/* Need to parse something */
			switch (parse_type) {
			default:
			case UCL_PARSE_UCL:
				return ucl_state_machine (parser);
			case UCL_PARSE_MSGPACK:
				return ucl_parse_msgpack (parser);
			case UCL_PARSE_CSEXP:
				return ucl_parse_csexp (parser);
			}
		}
		else {
			/* Just add empty chunk and go forward */
			if (parser->top_obj == NULL) {
				/*
				 * In case of empty object, create one to indicate that we've
				 * read something
				 */
				parser->top_obj = ucl_object_new_full (UCL_OBJECT, priority);
			}

			return true;
		}
	}

	ucl_create_err (&parser->err, "a parser is in an invalid state");

	return false;
}