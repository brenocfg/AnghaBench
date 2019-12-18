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
struct archive_read {TYPE_1__* format; } ;
struct _7zip {struct _7zip* tmp_stream_buff; struct _7zip** sub_stream_buff; struct _7zip* uncompressed_buffer; struct _7zip* entry_names; struct _7zip* entries; int /*<<< orphan*/  si; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct _7zip*) ; 
 int /*<<< orphan*/  free_StreamsInfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_decompression (struct archive_read*,struct _7zip*) ; 

__attribute__((used)) static int
archive_read_format_7zip_cleanup(struct archive_read *a)
{
	struct _7zip *zip;

	zip = (struct _7zip *)(a->format->data);
	free_StreamsInfo(&(zip->si));
	free(zip->entries);
	free(zip->entry_names);
	free_decompression(a, zip);
	free(zip->uncompressed_buffer);
	free(zip->sub_stream_buff[0]);
	free(zip->sub_stream_buff[1]);
	free(zip->sub_stream_buff[2]);
	free(zip->tmp_stream_buff);
	free(zip);
	(a->format->data) = NULL;
	return (ARCHIVE_OK);
}