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
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_BLOB ; 
 int /*<<< orphan*/  O_RDONLY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_path (struct strbuf*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  index_fd (int /*<<< orphan*/ *,struct object_id*,int,struct stat*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 int /*<<< orphan*/  lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 scalar_t__ oideq (struct object_id*,struct object_id*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  the_index ; 

__attribute__((used)) static int use_wt_file(const char *workdir, const char *name,
		       struct object_id *oid)
{
	struct strbuf buf = STRBUF_INIT;
	struct stat st;
	int use = 0;

	strbuf_addstr(&buf, workdir);
	add_path(&buf, buf.len, name);

	if (!lstat(buf.buf, &st) && !S_ISLNK(st.st_mode)) {
		struct object_id wt_oid;
		int fd = open(buf.buf, O_RDONLY);

		if (fd >= 0 &&
		    !index_fd(&the_index, &wt_oid, fd, &st, OBJ_BLOB, name, 0)) {
			if (is_null_oid(oid)) {
				oidcpy(oid, &wt_oid);
				use = 1;
			} else if (oideq(oid, &wt_oid))
				use = 1;
		}
	}

	strbuf_release(&buf);

	return use;
}