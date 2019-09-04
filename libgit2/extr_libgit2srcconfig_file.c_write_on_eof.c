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
struct write_data {int /*<<< orphan*/  orig_section; int /*<<< orphan*/  buf; int /*<<< orphan*/  section; scalar_t__ value; int /*<<< orphan*/  preg_replaced; int /*<<< orphan*/  preg; TYPE_1__ buffered_comment; } ;
typedef  int /*<<< orphan*/  git_config_parser ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int git_buf_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int write_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write_value (struct write_data*) ; 

__attribute__((used)) static int write_on_eof(
	git_config_parser *reader, const char *current_section, void *data)
{
	struct write_data *write_data = (struct write_data *)data;
	int result = 0;

	GIT_UNUSED(reader);

	/*
	 * If we've buffered comments when reaching EOF, make sure to dump them.
	 */
	if ((result = git_buf_put(write_data->buf, write_data->buffered_comment.ptr, write_data->buffered_comment.size)) < 0)
		return result;

	/* If we are at the EOF and have not written our value (again, for a
	 * simple name/value set, not a multivar) then we have never seen the
	 * section in question and should create a new section and write the
	 * value.
	 */
	if ((!write_data->preg || !write_data->preg_replaced) && write_data->value) {
		/* write the section header unless we're already in it */
		if (!current_section || strcmp(current_section, write_data->section))
			result = write_section(write_data->buf, write_data->orig_section);

		if (!result)
			result = write_value(write_data);
	}

	return result;
}