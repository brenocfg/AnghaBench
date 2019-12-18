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
struct ucl_chunk {unsigned char* pos; unsigned char const* end; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCL_CHARACTER_ESCAPE ; 
 int /*<<< orphan*/  UCL_CHARACTER_UCL_UNSAFE ; 
 int /*<<< orphan*/  UCL_ESYNTAX ; 
 int /*<<< orphan*/  isxdigit (unsigned char const) ; 
 int /*<<< orphan*/  ucl_chunk_skipc (struct ucl_chunk*,unsigned char const*) ; 
 int /*<<< orphan*/  ucl_set_err (struct ucl_parser*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ucl_test_character (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ucl_lex_json_string (struct ucl_parser *parser,
		struct ucl_chunk *chunk, bool *need_unescape, bool *ucl_escape, bool *var_expand)
{
	const unsigned char *p = chunk->pos;
	unsigned char c;
	int i;

	while (p < chunk->end) {
		c = *p;
		if (c < 0x1F) {
			/* Unmasked control character */
			if (c == '\n') {
				ucl_set_err (parser, UCL_ESYNTAX, "unexpected newline",
						&parser->err);
			}
			else {
				ucl_set_err (parser, UCL_ESYNTAX, "unexpected control character",
						&parser->err);
			}
			return false;
		}
		else if (c == '\\') {
			ucl_chunk_skipc (chunk, p);
			c = *p;
			if (p >= chunk->end) {
				ucl_set_err (parser, UCL_ESYNTAX, "unfinished escape character",
						&parser->err);
				return false;
			}
			else if (ucl_test_character (c, UCL_CHARACTER_ESCAPE)) {
				if (c == 'u') {
					ucl_chunk_skipc (chunk, p);
					for (i = 0; i < 4 && p < chunk->end; i ++) {
						if (!isxdigit (*p)) {
							ucl_set_err (parser, UCL_ESYNTAX, "invalid utf escape",
									&parser->err);
							return false;
						}
						ucl_chunk_skipc (chunk, p);
					}
					if (p >= chunk->end) {
						ucl_set_err (parser, UCL_ESYNTAX, "unfinished escape character",
								&parser->err);
						return false;
					}
				}
				else {
					ucl_chunk_skipc (chunk, p);
				}
			}
			*need_unescape = true;
			*ucl_escape = true;
			continue;
		}
		else if (c == '"') {
			ucl_chunk_skipc (chunk, p);
			return true;
		}
		else if (ucl_test_character (c, UCL_CHARACTER_UCL_UNSAFE)) {
			*ucl_escape = true;
		}
		else if (c == '$') {
			*var_expand = true;
		}
		ucl_chunk_skipc (chunk, p);
	}

	ucl_set_err (parser, UCL_ESYNTAX, "no quote at the end of json string",
			&parser->err);
	return false;
}