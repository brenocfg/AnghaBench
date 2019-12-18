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
struct archive_write_program_data {int child_stdin; int child_stdout; int /*<<< orphan*/  program_name; } ;

/* Variables and functions */
 struct archive_write_program_data* calloc (int,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

struct archive_write_program_data *
__archive_write_program_allocate(const char *program)
{
	struct archive_write_program_data *data;

	data = calloc(1, sizeof(struct archive_write_program_data));
	if (data == NULL)
		return (data);
	data->child_stdin = -1;
	data->child_stdout = -1;
	data->program_name = strdup(program);
	return (data);
}