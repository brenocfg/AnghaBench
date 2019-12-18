#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ allow_textconv; } ;
struct diff_options {int /*<<< orphan*/  repo; TYPE_1__ flags; } ;
struct TYPE_5__ {unsigned long size; int /*<<< orphan*/  ptr; } ;
struct blame_origin {TYPE_2__ file; int /*<<< orphan*/  path; int /*<<< orphan*/  blob_oid; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ mmfile_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_origin_fingerprints (struct blame_origin*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 
 scalar_t__ textconv_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned long*) ; 

__attribute__((used)) static void fill_origin_blob(struct diff_options *opt,
			     struct blame_origin *o, mmfile_t *file,
			     int *num_read_blob, int fill_fingerprints)
{
	if (!o->file.ptr) {
		enum object_type type;
		unsigned long file_size;

		(*num_read_blob)++;
		if (opt->flags.allow_textconv &&
		    textconv_object(opt->repo, o->path, o->mode,
				    &o->blob_oid, 1, &file->ptr, &file_size))
			;
		else
			file->ptr = read_object_file(&o->blob_oid, &type,
						     &file_size);
		file->size = file_size;

		if (!file->ptr)
			die("Cannot read blob %s for path %s",
			    oid_to_hex(&o->blob_oid),
			    o->path);
		o->file = *file;
	}
	else
		*file = o->file;
	if (fill_fingerprints)
		fill_origin_fingerprints(o);
}