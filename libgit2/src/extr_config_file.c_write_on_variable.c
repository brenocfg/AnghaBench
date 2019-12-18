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
struct write_data {int preg_replaced; int /*<<< orphan*/  value; int /*<<< orphan*/ * preg; int /*<<< orphan*/  name; scalar_t__ in_section; TYPE_1__ buffered_comment; int /*<<< orphan*/  buf; } ;
typedef  char const git_config_parser ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int git_buf_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_regexp_match (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int write_line (struct write_data*,char const*,size_t) ; 
 int write_value (struct write_data*) ; 

__attribute__((used)) static int write_on_variable(
	git_config_parser *reader,
	const char *current_section,
	const char *var_name,
	const char *var_value,
	const char *line,
	size_t line_len,
	void *data)
{
	struct write_data *write_data = (struct write_data *)data;
	bool has_matched = false;
	int error;

	GIT_UNUSED(reader);
	GIT_UNUSED(current_section);

	/*
	 * If there were comments just before this variable, let's dump them as well.
	 */
	if ((error = git_buf_put(write_data->buf, write_data->buffered_comment.ptr, write_data->buffered_comment.size)) < 0)
		return error;

	git_buf_clear(&write_data->buffered_comment);

	/* See if we are to update this name/value pair; first examine name */
	if (write_data->in_section &&
		strcasecmp(write_data->name, var_name) == 0)
		has_matched = true;

	/* If we have a regex to match the value, see if it matches */
	if (has_matched && write_data->preg != NULL)
		has_matched = (git_regexp_match(write_data->preg, var_value) == 0);

	/* If this isn't the name/value we're looking for, simply dump the
	 * existing data back out and continue on.
	 */
	if (!has_matched)
		return write_line(write_data, line, line_len);

	write_data->preg_replaced = 1;

	/* If value is NULL, we are deleting this value; write nothing. */
	if (!write_data->value)
		return 0;

	return write_value(write_data);
}