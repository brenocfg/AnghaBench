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
struct ucl_parser {int /*<<< orphan*/  cur_file; int /*<<< orphan*/  err; } ;
typedef  enum ucl_parse_type { ____Placeholder_ucl_parse_type } ucl_parse_type ;
typedef  enum ucl_duplicate_strategy { ____Placeholder_ucl_duplicate_strategy } ucl_duplicate_strategy ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_fetch_file (char*,unsigned char**,size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ucl_munmap (unsigned char*,size_t) ; 
 int ucl_parser_add_chunk_full (struct ucl_parser*,unsigned char*,size_t,unsigned int,int,int) ; 
 int /*<<< orphan*/  ucl_parser_set_filevars (struct ucl_parser*,char*,int) ; 
 int /*<<< orphan*/ * ucl_realpath (char const*,char*) ; 

bool
ucl_parser_add_file_full (struct ucl_parser *parser, const char *filename,
		unsigned priority, enum ucl_duplicate_strategy strat,
		enum ucl_parse_type parse_type)
{
	unsigned char *buf;
	size_t len;
	bool ret;
	char realbuf[PATH_MAX];

	if (ucl_realpath (filename, realbuf) == NULL) {
		ucl_create_err (&parser->err, "cannot open file %s: %s",
				filename,
				strerror (errno));
		return false;
	}

	if (!ucl_fetch_file (realbuf, &buf, &len, &parser->err, true)) {
		return false;
	}

	if (parser->cur_file) {
		free (parser->cur_file);
	}
	parser->cur_file = strdup (realbuf);
	ucl_parser_set_filevars (parser, realbuf, false);
	ret = ucl_parser_add_chunk_full (parser, buf, len, priority, strat,
			parse_type);

	if (len > 0) {
		ucl_munmap (buf, len);
	}

	return ret;
}