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
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
struct write_data {int in_section; TYPE_1__ buffered_comment; int /*<<< orphan*/  buf; int /*<<< orphan*/  section; scalar_t__ value; int /*<<< orphan*/  preg; } ;
typedef  int /*<<< orphan*/  git_config_parser ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int git_buf_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int write_line (struct write_data*,char const*,size_t) ; 
 int write_value (struct write_data*) ; 

__attribute__((used)) static int write_on_section(
	git_config_parser *reader,
	const char *current_section,
	const char *line,
	size_t line_len,
	void *data)
{
	struct write_data *write_data = (struct write_data *)data;
	int result = 0;

	GIT_UNUSED(reader);

	/* If we were previously in the correct section (but aren't anymore)
	 * and haven't written our value (for a simple name/value set, not
	 * a multivar), then append it to the end of the section before writing
	 * the new one.
	 */
	if (write_data->in_section && !write_data->preg && write_data->value)
		result = write_value(write_data);

	write_data->in_section = strcmp(current_section, write_data->section) == 0;

	/*
	 * If there were comments just before this section, dump them as well.
	 */
	if (!result) {
		result = git_buf_put(write_data->buf, write_data->buffered_comment.ptr, write_data->buffered_comment.size);
		git_buf_clear(&write_data->buffered_comment);
	}

	if (!result)
		result = write_line(write_data, line, line_len);

	return result;
}