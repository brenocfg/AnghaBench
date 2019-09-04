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
struct ref_store {int dummy; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_STORE_WRITE ; 
 struct strbuf STRBUF_INIT ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int remove_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int files_delete_reflog(struct ref_store *ref_store,
			       const char *refname)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "delete_reflog");
	struct strbuf sb = STRBUF_INIT;
	int ret;

	files_reflog_path(refs, &sb, refname);
	ret = remove_path(sb.buf);
	strbuf_release(&sb);
	return ret;
}