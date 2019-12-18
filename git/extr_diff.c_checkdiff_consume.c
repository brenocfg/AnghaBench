#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct checkdiff_t {int conflict_marker_size; char* lineno; int status; int filename; TYPE_1__* o; int /*<<< orphan*/  ws_rule; } ;
struct TYPE_4__ {int /*<<< orphan*/  file; int /*<<< orphan*/  use_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_FILE_NEW ; 
 int /*<<< orphan*/  DIFF_RESET ; 
 int /*<<< orphan*/  DIFF_WHITESPACE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* diff_get_color (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* diff_line_prefix (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_line (TYPE_1__*,char const*,char const*,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_conflict_marker (char*,int,unsigned long) ; 
 char* whitespace_error_string (unsigned int) ; 
 unsigned int ws_check (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws_check_emit (char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 

__attribute__((used)) static void checkdiff_consume(void *priv, char *line, unsigned long len)
{
	struct checkdiff_t *data = priv;
	int marker_size = data->conflict_marker_size;
	const char *ws = diff_get_color(data->o->use_color, DIFF_WHITESPACE);
	const char *reset = diff_get_color(data->o->use_color, DIFF_RESET);
	const char *set = diff_get_color(data->o->use_color, DIFF_FILE_NEW);
	char *err;
	const char *line_prefix;

	assert(data->o);
	line_prefix = diff_line_prefix(data->o);

	if (line[0] == '+') {
		unsigned bad;
		data->lineno++;
		if (is_conflict_marker(line + 1, marker_size, len - 1)) {
			data->status |= 1;
			fprintf(data->o->file,
				"%s%s:%d: leftover conflict marker\n",
				line_prefix, data->filename, data->lineno);
		}
		bad = ws_check(line + 1, len - 1, data->ws_rule);
		if (!bad)
			return;
		data->status |= bad;
		err = whitespace_error_string(bad);
		fprintf(data->o->file, "%s%s:%d: %s.\n",
			line_prefix, data->filename, data->lineno, err);
		free(err);
		emit_line(data->o, set, reset, line, 1);
		ws_check_emit(line + 1, len - 1, data->ws_rule,
			      data->o->file, set, reset, ws);
	} else if (line[0] == ' ') {
		data->lineno++;
	}
}