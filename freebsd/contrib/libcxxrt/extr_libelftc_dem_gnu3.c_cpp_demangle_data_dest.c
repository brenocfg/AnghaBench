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
struct cpp_demangle_data {int /*<<< orphan*/  output; int /*<<< orphan*/  output_tmp; int /*<<< orphan*/  subst; int /*<<< orphan*/  tmpl; int /*<<< orphan*/  class_type; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  vector_read_cmd_dest (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vector_str_dest (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cpp_demangle_data_dest(struct cpp_demangle_data *d)
{

	if (d == NULL)
		return;

	vector_read_cmd_dest(&d->cmd);
	vector_str_dest(&d->class_type);
	vector_str_dest(&d->tmpl);
	vector_str_dest(&d->subst);
	vector_str_dest(&d->output_tmp);
	vector_str_dest(&d->output);
}