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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct ref_store {int dummy; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_STORE_READ ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/  lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int files_reflog_exists(struct ref_store *ref_store,
			       const char *refname)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ, "reflog_exists");
	struct strbuf sb = STRBUF_INIT;
	struct stat st;
	int ret;

	files_reflog_path(refs, &sb, refname);
	ret = !lstat(sb.buf, &st) && S_ISREG(st.st_mode);
	strbuf_release(&sb);
	return ret;
}