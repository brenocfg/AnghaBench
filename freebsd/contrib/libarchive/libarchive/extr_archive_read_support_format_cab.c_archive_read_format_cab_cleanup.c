#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cfheader {int folder_count; int file_count; struct cab* file_array; struct cab* folder_array; } ;
struct TYPE_3__ {struct cab* memimage; } ;
struct cab {struct cab* uncompressed_buffer; int /*<<< orphan*/  ws; int /*<<< orphan*/  xstrm; int /*<<< orphan*/  stream; scalar_t__ stream_valid; int /*<<< orphan*/  pathname; struct cfheader cfheader; TYPE_1__ cfdata; } ;
struct archive_read {TYPE_2__* format; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_wstring_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct cab*) ; 
 int /*<<< orphan*/  inflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lzx_decode_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
archive_read_format_cab_cleanup(struct archive_read *a)
{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfheader *hd = &cab->cfheader;
	int i;

	if (hd->folder_array != NULL) {
		for (i = 0; i < hd->folder_count; i++)
			free(hd->folder_array[i].cfdata.memimage);
		free(hd->folder_array);
	}
	if (hd->file_array != NULL) {
		for (i = 0; i < cab->cfheader.file_count; i++)
			archive_string_free(&(hd->file_array[i].pathname));
		free(hd->file_array);
	}
#ifdef HAVE_ZLIB_H
	if (cab->stream_valid)
		inflateEnd(&cab->stream);
#endif
	lzx_decode_free(&cab->xstrm);
	archive_wstring_free(&cab->ws);
	free(cab->uncompressed_buffer);
	free(cab);
	(a->format->data) = NULL;
	return (ARCHIVE_OK);
}