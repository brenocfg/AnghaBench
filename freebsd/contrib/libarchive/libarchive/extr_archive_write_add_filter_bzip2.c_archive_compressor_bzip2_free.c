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
struct private_data {int /*<<< orphan*/  pdata; } ;
struct archive_write_filter {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  __archive_write_program_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct private_data*) ; 

__attribute__((used)) static int
archive_compressor_bzip2_free(struct archive_write_filter *f)
{
	struct private_data *data = (struct private_data *)f->data;

	__archive_write_program_free(data->pdata);
	free(data);
	return (ARCHIVE_OK);
}