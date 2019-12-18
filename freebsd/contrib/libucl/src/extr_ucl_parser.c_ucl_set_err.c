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
struct ucl_parser {char* cur_file; int err_code; struct ucl_chunk* chunks; } ;
struct ucl_chunk {int /*<<< orphan*/ * pos; int /*<<< orphan*/  column; int /*<<< orphan*/  line; int /*<<< orphan*/ * end; } ;
typedef  int /*<<< orphan*/  UT_string ;

/* Variables and functions */
 scalar_t__ isgraph (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ **,char const*,char const*,char const*,...) ; 

__attribute__((used)) static inline void
ucl_set_err (struct ucl_parser *parser, int code, const char *str, UT_string **err)
{
	const char *fmt_string, *filename;
	struct ucl_chunk *chunk = parser->chunks;

	if (parser->cur_file) {
		filename = parser->cur_file;
	}
	else {
		filename = "<unknown>";
	}

	if (chunk->pos < chunk->end) {
		if (isgraph (*chunk->pos)) {
			fmt_string = "error while parsing %s: "
					"line: %d, column: %d - '%s', character: '%c'";
		}
		else {
			fmt_string = "error while parsing %s: "
					"line: %d, column: %d - '%s', character: '0x%02x'";
		}
		ucl_create_err (err, fmt_string,
			filename, chunk->line, chunk->column,
			str, *chunk->pos);
	}
	else {
		ucl_create_err (err, "error while parsing %s: at the end of chunk: %s",
			filename, str);
	}

	parser->err_code = code;
}