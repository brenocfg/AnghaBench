#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ blocks; scalar_t__ offset_of_temp; struct TYPE_8__* next; } ;
struct isofile {TYPE_4__* cur_content; TYPE_4__ content; int /*<<< orphan*/  write_content; struct isofile* datanext; } ;
struct TYPE_7__ {struct isofile* first; } ;
struct TYPE_6__ {TYPE_1__* boot; int /*<<< orphan*/ * catalog; } ;
struct iso9660 {TYPE_3__ data_file_list; TYPE_2__ el_torito; } ;
struct archive_write {struct iso9660* format_data; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {struct isofile* file; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 scalar_t__ LOGICAL_BLOCK_BITS ; 
 int make_boot_catalog (struct archive_write*) ; 
 int write_file_contents (struct archive_write*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
write_file_descriptors(struct archive_write *a)
{
	struct iso9660 *iso9660 = a->format_data;
	struct isofile *file;
	int64_t blocks, offset;
	int r;

	blocks = 0;
	offset = 0;

	/* Make the boot catalog contents, and write it. */
	if (iso9660->el_torito.catalog != NULL) {
		r = make_boot_catalog(a);
		if (r < 0)
			return (r);
	}

	/* Write the boot file contents. */
	if (iso9660->el_torito.boot != NULL) {
		file = iso9660->el_torito.boot->file;
		blocks = file->content.blocks;
		offset = file->content.offset_of_temp;
		if (offset != 0) {
			r = write_file_contents(a, offset,
			    blocks << LOGICAL_BLOCK_BITS);
			if (r < 0)
				return (r);
			blocks = 0;
			offset = 0;
		}
	}

	/* Write out all file contents. */
	for (file = iso9660->data_file_list.first;
	    file != NULL; file = file->datanext) {

		if (!file->write_content)
			continue;

		if ((offset + (blocks << LOGICAL_BLOCK_BITS)) <
		     file->content.offset_of_temp) {
			if (blocks > 0) {
				r = write_file_contents(a, offset,
				    blocks << LOGICAL_BLOCK_BITS);
				if (r < 0)
					return (r);
			}
			blocks = 0;
			offset = file->content.offset_of_temp;
		}

		file->cur_content = &(file->content);
		do {
			blocks += file->cur_content->blocks;
			/* Next fragment */
			file->cur_content = file->cur_content->next;
		} while (file->cur_content != NULL);
	}

	/* Flush out remaining blocks. */
	if (blocks > 0) {
		r = write_file_contents(a, offset,
		    blocks << LOGICAL_BLOCK_BITS);
		if (r < 0)
			return (r);
	}

	return (ARCHIVE_OK);
}