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
struct private_data {int /*<<< orphan*/  pdata; int /*<<< orphan*/  description; struct private_data* cmd; } ;
struct archive_write_filter {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  __archive_write_program_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct private_data*) ; 

__attribute__((used)) static int
archive_compressor_program_free(struct archive_write_filter *f)
{
	struct private_data *data = (struct private_data *)f->data;

	if (data) {
		free(data->cmd);
		archive_string_free(&data->description);
		__archive_write_program_free(data->pdata);
		free(data);
		f->data = NULL;
	}
	return (ARCHIVE_OK);
}