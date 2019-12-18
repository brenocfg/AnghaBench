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
struct files_ref_store {unsigned int store_flags; int /*<<< orphan*/  gitcommondir; int /*<<< orphan*/  gitdir; int /*<<< orphan*/  packed_ref_store; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  base_ref_store_init (struct ref_store*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chdir_notify_reparent (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_common_dir_noenv (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  packed_ref_store_create (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  refs_be_files ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct files_ref_store* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static struct ref_store *files_ref_store_create(const char *gitdir,
						unsigned int flags)
{
	struct files_ref_store *refs = xcalloc(1, sizeof(*refs));
	struct ref_store *ref_store = (struct ref_store *)refs;
	struct strbuf sb = STRBUF_INIT;

	base_ref_store_init(ref_store, &refs_be_files);
	refs->store_flags = flags;

	refs->gitdir = xstrdup(gitdir);
	get_common_dir_noenv(&sb, gitdir);
	refs->gitcommondir = strbuf_detach(&sb, NULL);
	strbuf_addf(&sb, "%s/packed-refs", refs->gitcommondir);
	refs->packed_ref_store = packed_ref_store_create(sb.buf, flags);
	strbuf_release(&sb);

	chdir_notify_reparent("files-backend $GIT_DIR",
			      &refs->gitdir);
	chdir_notify_reparent("files-backend $GIT_COMMONDIR",
			      &refs->gitcommondir);

	return ref_store;
}