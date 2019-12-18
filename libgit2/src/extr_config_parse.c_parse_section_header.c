#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  line_len; int /*<<< orphan*/  line; } ;
struct TYPE_6__ {TYPE_5__ ctx; } ;
typedef  TYPE_1__ git_config_parser ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  config_keychar (int) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 scalar_t__ git__isspace (int) ; 
 char* git__malloc (size_t) ; 
 char* git__strndup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git__tolower (int) ; 
 int /*<<< orphan*/  git_parse_advance_ws (TYPE_5__*) ; 
 int parse_subsection_header (TYPE_1__*,char*,int,char*,char**) ; 
 int /*<<< orphan*/  set_parse_error (TYPE_1__*,int,char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int parse_section_header(git_config_parser *reader, char **section_out)
{
	char *name, *name_end;
	int name_length, c, pos;
	int result;
	char *line;
	size_t line_len;

	git_parse_advance_ws(&reader->ctx);
	line = git__strndup(reader->ctx.line, reader->ctx.line_len);
	if (line == NULL)
		return -1;

	/* find the end of the variable's name */
	name_end = strrchr(line, ']');
	if (name_end == NULL) {
		git__free(line);
		set_parse_error(reader, 0, "missing ']' in section header");
		return -1;
	}

	GIT_ERROR_CHECK_ALLOC_ADD(&line_len, (size_t)(name_end - line), 1);
	name = git__malloc(line_len);
	GIT_ERROR_CHECK_ALLOC(name);

	name_length = 0;
	pos = 0;

	/* Make sure we were given a section header */
	c = line[pos++];
	assert(c == '[');

	c = line[pos++];

	do {
		if (git__isspace(c)){
			name[name_length] = '\0';
			result = parse_subsection_header(reader, line, pos, name, section_out);
			git__free(line);
			git__free(name);
			return result;
		}

		if (!config_keychar(c) && c != '.') {
			set_parse_error(reader, pos, "unexpected character in header");
			goto fail_parse;
		}

		name[name_length++] = (char)git__tolower(c);

	} while ((c = line[pos++]) != ']');

	if (line[pos - 1] != ']') {
		set_parse_error(reader, pos, "unexpected end of file");
		goto fail_parse;
	}

	git__free(line);

	name[name_length] = 0;
	*section_out = name;

	return pos;

fail_parse:
	git__free(line);
	git__free(name);
	return -1;
}