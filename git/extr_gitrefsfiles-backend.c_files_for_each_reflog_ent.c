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
typedef  int /*<<< orphan*/  each_reflog_ent_fn ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  REF_STORE_READ ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 struct files_ref_store* files_downcast (struct ref_store*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char const*) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int show_one_reflog_ent (struct strbuf*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int files_for_each_reflog_ent(struct ref_store *ref_store,
				     const char *refname,
				     each_reflog_ent_fn fn, void *cb_data)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_READ,
			       "for_each_reflog_ent");
	FILE *logfp;
	struct strbuf sb = STRBUF_INIT;
	int ret = 0;

	files_reflog_path(refs, &sb, refname);
	logfp = fopen(sb.buf, "r");
	strbuf_release(&sb);
	if (!logfp)
		return -1;

	while (!ret && !strbuf_getwholeline(&sb, logfp, '\n'))
		ret = show_one_reflog_ent(&sb, fn, cb_data);
	fclose(logfp);
	strbuf_release(&sb);
	return ret;
}