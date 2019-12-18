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
struct tar {int /*<<< orphan*/  localname; int /*<<< orphan*/  longlink; int /*<<< orphan*/  longname; int /*<<< orphan*/  pax_header; int /*<<< orphan*/  pax_global; int /*<<< orphan*/  line; int /*<<< orphan*/  entry_gname; int /*<<< orphan*/  entry_uname; int /*<<< orphan*/  entry_linkpath; int /*<<< orphan*/  entry_pathname_override; int /*<<< orphan*/  entry_pathname; int /*<<< orphan*/  acl_text; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct tar*) ; 
 int /*<<< orphan*/  gnu_clear_sparse_list (struct tar*) ; 

__attribute__((used)) static int
archive_read_format_tar_cleanup(struct archive_read *a)
{
	struct tar *tar;

	tar = (struct tar *)(a->format->data);
	gnu_clear_sparse_list(tar);
	archive_string_free(&tar->acl_text);
	archive_string_free(&tar->entry_pathname);
	archive_string_free(&tar->entry_pathname_override);
	archive_string_free(&tar->entry_linkpath);
	archive_string_free(&tar->entry_uname);
	archive_string_free(&tar->entry_gname);
	archive_string_free(&tar->line);
	archive_string_free(&tar->pax_global);
	archive_string_free(&tar->pax_header);
	archive_string_free(&tar->longname);
	archive_string_free(&tar->longlink);
	archive_string_free(&tar->localname);
	free(tar);
	(a->format->data) = NULL;
	return (ARCHIVE_OK);
}