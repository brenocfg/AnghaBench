#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {unsigned long len; void* buf; } ;
struct object_id {int dummy; } ;
struct index_state {int dummy; } ;
struct diff_tempfile {int /*<<< orphan*/  mode; int /*<<< orphan*/  hex; TYPE_1__* tempfile; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* basename (char*) ; 
 scalar_t__ close_tempfile_gently (TYPE_1__*) ; 
 scalar_t__ convert_to_working_tree (struct index_state*,char const*,char const*,size_t,struct strbuf*) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_tempfile_path (TYPE_1__*) ; 
 TYPE_1__* mks_tempfile_ts (void*,scalar_t__) ; 
 int /*<<< orphan*/  oid_to_hex_r (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ write_in_full (int /*<<< orphan*/ ,void*,unsigned long) ; 
 int /*<<< orphan*/  xsnprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void prep_temp_blob(struct index_state *istate,
			   const char *path, struct diff_tempfile *temp,
			   void *blob,
			   unsigned long size,
			   const struct object_id *oid,
			   int mode)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf tempfile = STRBUF_INIT;
	char *path_dup = xstrdup(path);
	const char *base = basename(path_dup);

	/* Generate "XXXXXX_basename.ext" */
	strbuf_addstr(&tempfile, "XXXXXX_");
	strbuf_addstr(&tempfile, base);

	temp->tempfile = mks_tempfile_ts(tempfile.buf, strlen(base) + 1);
	if (!temp->tempfile)
		die_errno("unable to create temp-file");
	if (convert_to_working_tree(istate, path,
			(const char *)blob, (size_t)size, &buf)) {
		blob = buf.buf;
		size = buf.len;
	}
	if (write_in_full(temp->tempfile->fd, blob, size) < 0 ||
	    close_tempfile_gently(temp->tempfile))
		die_errno("unable to write temp-file");
	temp->name = get_tempfile_path(temp->tempfile);
	oid_to_hex_r(temp->hex, oid);
	xsnprintf(temp->mode, sizeof(temp->mode), "%06o", mode);
	strbuf_release(&buf);
	strbuf_release(&tempfile);
	free(path_dup);
}