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
 int /*<<< orphan*/  files_ref_path (struct files_ref_store*,struct strbuf*,char*) ; 
 int /*<<< orphan*/  safe_create_dir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static int files_init_db(struct ref_store *ref_store, struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE, "init_db");
	struct strbuf sb = STRBUF_INIT;

	/*
	 * Create .git/refs/{heads,tags}
	 */
	files_ref_path(refs, &sb, "refs/heads");
	safe_create_dir(sb.buf, 1);

	strbuf_reset(&sb);
	files_ref_path(refs, &sb, "refs/tags");
	safe_create_dir(sb.buf, 1);

	strbuf_release(&sb);
	return 0;
}