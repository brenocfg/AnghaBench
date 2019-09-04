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
struct userdiff_driver {int dummy; } ;
struct strbuf {unsigned long len; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_filespec {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_BLOB ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 struct diff_filespec* alloc_filespec (char const*) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_filespec (struct diff_filespec*,struct object_id const*,int,unsigned int) ; 
 unsigned long fill_textconv (struct repository*,struct userdiff_driver*,struct diff_filespec*,char**) ; 
 int /*<<< orphan*/  free_filespec (struct diff_filespec*) ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 char* read_object_file (struct object_id const*,int*,unsigned long*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 char* xcalloc (int,int) ; 

__attribute__((used)) static char *grab_blob(struct repository *r,
		       const struct object_id *oid, unsigned int mode,
		       unsigned long *size, struct userdiff_driver *textconv,
		       const char *path)
{
	char *blob;
	enum object_type type;

	if (S_ISGITLINK(mode)) {
		struct strbuf buf = STRBUF_INIT;
		strbuf_addf(&buf, "Subproject commit %s\n", oid_to_hex(oid));
		*size = buf.len;
		blob = strbuf_detach(&buf, NULL);
	} else if (is_null_oid(oid)) {
		/* deleted blob */
		*size = 0;
		return xcalloc(1, 1);
	} else if (textconv) {
		struct diff_filespec *df = alloc_filespec(path);
		fill_filespec(df, oid, 1, mode);
		*size = fill_textconv(r, textconv, df, &blob);
		free_filespec(df);
	} else {
		blob = read_object_file(oid, &type, size);
		if (type != OBJ_BLOB)
			die("object '%s' is not a blob!", oid_to_hex(oid));
	}
	return blob;
}