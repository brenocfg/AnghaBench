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
struct userdiff_driver {int /*<<< orphan*/  textconv; } ;
struct repository {int dummy; } ;
struct grep_source {int type; char* buf; size_t size; int /*<<< orphan*/ * identifier; int /*<<< orphan*/  path; } ;
struct diff_filespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  GREP_SOURCE_FILE 129 
#define  GREP_SOURCE_OID 128 
 struct diff_filespec* alloc_filespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_filespec (struct diff_filespec*,int /*<<< orphan*/ *,int,int) ; 
 size_t fill_textconv (struct repository*,struct userdiff_driver*,struct diff_filespec*,char**) ; 
 int /*<<< orphan*/  free_filespec (struct diff_filespec*) ; 
 int /*<<< orphan*/  grep_read_lock () ; 
 int /*<<< orphan*/  grep_read_unlock () ; 
 int /*<<< orphan*/  grep_source_clear_data (struct grep_source*) ; 
 int grep_source_load (struct grep_source*) ; 
 int /*<<< orphan*/  null_oid ; 

__attribute__((used)) static int fill_textconv_grep(struct repository *r,
			      struct userdiff_driver *driver,
			      struct grep_source *gs)
{
	struct diff_filespec *df;
	char *buf;
	size_t size;

	if (!driver || !driver->textconv)
		return grep_source_load(gs);

	/*
	 * The textconv interface is intimately tied to diff_filespecs, so we
	 * have to pretend to be one. If we could unify the grep_source
	 * and diff_filespec structs, this mess could just go away.
	 */
	df = alloc_filespec(gs->path);
	switch (gs->type) {
	case GREP_SOURCE_OID:
		fill_filespec(df, gs->identifier, 1, 0100644);
		break;
	case GREP_SOURCE_FILE:
		fill_filespec(df, &null_oid, 0, 0100644);
		break;
	default:
		BUG("attempt to textconv something without a path?");
	}

	/*
	 * fill_textconv is not remotely thread-safe; it may load objects
	 * behind the scenes, and it modifies the global diff tempfile
	 * structure.
	 */
	grep_read_lock();
	size = fill_textconv(r, driver, df, &buf);
	grep_read_unlock();
	free_filespec(df);

	/*
	 * The normal fill_textconv usage by the diff machinery would just keep
	 * the textconv'd buf separate from the diff_filespec. But much of the
	 * grep code passes around a grep_source and assumes that its "buf"
	 * pointer is the beginning of the thing we are searching. So let's
	 * install our textconv'd version into the grep_source, taking care not
	 * to leak any existing buffer.
	 */
	grep_source_clear_data(gs);
	gs->buf = buf;
	gs->size = size;

	return 0;
}