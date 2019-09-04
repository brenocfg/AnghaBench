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
struct write_data {int /*<<< orphan*/ * value; int /*<<< orphan*/  preg; int /*<<< orphan*/  orig_name; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int git_buf_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,char const*) ; 
 char* quotes_for_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_value(struct write_data *write_data)
{
	const char *q;
	int result;

	q = quotes_for_value(write_data->value);
	result = git_buf_printf(write_data->buf,
		"\t%s = %s%s%s\n", write_data->orig_name, q, write_data->value, q);

	/* If we are updating a single name/value, we're done.  Setting `value`
	 * to `NULL` will prevent us from trying to write it again later (in
	 * `write_on_section`) if we see the same section repeated.
	 */
	if (!write_data->preg)
		write_data->value = NULL;

	return result;
}