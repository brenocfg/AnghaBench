#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucl_stack {scalar_t__ level; TYPE_1__* obj; struct ucl_stack* next; } ;
struct ucl_parser {int /*<<< orphan*/  err; struct ucl_stack* stack; TYPE_1__* cur_obj; } ;
struct ucl_chunk {unsigned char* pos; unsigned char const* end; int remain; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ UCL_ARRAY ; 
 int /*<<< orphan*/  UCL_CHARACTER_VALUE_END ; 
 int /*<<< orphan*/  UCL_CHARACTER_WHITESPACE ; 
 int /*<<< orphan*/  UCL_ESYNTAX ; 
 int /*<<< orphan*/  UCL_FREE (int,struct ucl_stack*) ; 
 scalar_t__ UCL_OBJECT ; 
 int /*<<< orphan*/  ucl_attach_comment (struct ucl_parser*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ucl_chunk_skipc (struct ucl_chunk*,unsigned char const*) ; 
 scalar_t__ ucl_lex_is_comment (unsigned char const,unsigned char const) ; 
 int /*<<< orphan*/  ucl_set_err (struct ucl_parser*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucl_skip_comments (struct ucl_parser*) ; 
 scalar_t__ ucl_test_character (unsigned char const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ucl_parse_after_value (struct ucl_parser *parser, struct ucl_chunk *chunk)
{
	const unsigned char *p;
	bool got_sep = false;
	struct ucl_stack *st;

	p = chunk->pos;

	while (p < chunk->end) {
		if (ucl_test_character (*p, UCL_CHARACTER_WHITESPACE)) {
			/* Skip whitespaces */
			ucl_chunk_skipc (chunk, p);
		}
		else if (chunk->remain >= 2 && ucl_lex_is_comment (p[0], p[1])) {
			/* Skip comment */
			if (!ucl_skip_comments (parser)) {
				return false;
			}
			/* Treat comment as a separator */
			got_sep = true;
			p = chunk->pos;
		}
		else if (ucl_test_character (*p, UCL_CHARACTER_VALUE_END)) {
			if (*p == '}' || *p == ']') {
				if (parser->stack == NULL) {
					ucl_set_err (parser, UCL_ESYNTAX,
							"end of array or object detected without corresponding start",
							&parser->err);
					return false;
				}
				if ((*p == '}' && parser->stack->obj->type == UCL_OBJECT) ||
						(*p == ']' && parser->stack->obj->type == UCL_ARRAY)) {

					/* Pop all nested objects from a stack */
					st = parser->stack;
					parser->stack = st->next;
					UCL_FREE (sizeof (struct ucl_stack), st);

					if (parser->cur_obj) {
						ucl_attach_comment (parser, parser->cur_obj, true);
					}

					while (parser->stack != NULL) {
						st = parser->stack;

						if (st->next == NULL || st->next->level == st->level) {
							break;
						}

						parser->stack = st->next;
						parser->cur_obj = st->obj;
						UCL_FREE (sizeof (struct ucl_stack), st);
					}
				}
				else {
					ucl_set_err (parser, UCL_ESYNTAX,
							"unexpected terminating symbol detected",
							&parser->err);
					return false;
				}

				if (parser->stack == NULL) {
					/* Ignore everything after a top object */
					return true;
				}
				else {
					ucl_chunk_skipc (chunk, p);
				}
				got_sep = true;
			}
			else {
				/* Got a separator */
				got_sep = true;
				ucl_chunk_skipc (chunk, p);
			}
		}
		else {
			/* Anything else */
			if (!got_sep) {
				ucl_set_err (parser, UCL_ESYNTAX, "delimiter is missing",
						&parser->err);
				return false;
			}
			return true;
		}
	}

	return true;
}