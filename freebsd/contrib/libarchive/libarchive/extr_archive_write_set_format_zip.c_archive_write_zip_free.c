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
struct zip {int /*<<< orphan*/  hctx; scalar_t__ hctx_valid; int /*<<< orphan*/  cctx; scalar_t__ cctx_valid; int /*<<< orphan*/  entry; struct zip* buf; struct zip* buff; struct zip* next; struct zip* central_directory; } ;
struct cd_segment {int /*<<< orphan*/  hctx; scalar_t__ hctx_valid; int /*<<< orphan*/  cctx; scalar_t__ cctx_valid; int /*<<< orphan*/  entry; struct cd_segment* buf; struct cd_segment* buff; struct cd_segment* next; struct cd_segment* central_directory; } ;
struct archive_write {struct zip* format_data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_encrypto_aes_ctr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_hmac_sha1_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct zip*) ; 

__attribute__((used)) static int
archive_write_zip_free(struct archive_write *a)
{
	struct zip *zip;
	struct cd_segment *segment;

	zip = a->format_data;
	while (zip->central_directory != NULL) {
		segment = zip->central_directory;
		zip->central_directory = segment->next;
		free(segment->buff);
		free(segment);
	}
	free(zip->buf);
	archive_entry_free(zip->entry);
	if (zip->cctx_valid)
		archive_encrypto_aes_ctr_release(&zip->cctx);
	if (zip->hctx_valid)
		archive_hmac_sha1_cleanup(&zip->hctx);
	/* TODO: Free opt_sconv, sconv_default */

	free(zip);
	a->format_data = NULL;
	return (ARCHIVE_OK);
}