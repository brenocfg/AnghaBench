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
struct write_lzop {int /*<<< orphan*/  pdata; struct write_lzop* work_buffer; struct write_lzop* compressed; struct write_lzop* uncompressed; } ;
struct archive_write_filter {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  __archive_write_program_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct write_lzop*) ; 

__attribute__((used)) static int
archive_write_lzop_free(struct archive_write_filter *f)
{
	struct write_lzop *data = (struct write_lzop *)f->data;

#if defined(HAVE_LZO_LZOCONF_H) && defined(HAVE_LZO_LZO1X_H)
	free(data->uncompressed);
	free(data->compressed);
	free(data->work_buffer);
#else
	__archive_write_program_free(data->pdata);
#endif
	free(data);
	return (ARCHIVE_OK);
}