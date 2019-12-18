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
struct ref_iterator {int dummy; } ;
struct files_reflog_iterator {struct ref_store* ref_store; struct dir_iterator* dir_iterator; struct ref_iterator base; } ;
struct dir_iterator {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  base_ref_iterator_init (struct ref_iterator*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dir_iterator* dir_iterator_begin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ref_iterator* empty_ref_iterator_begin () ; 
 int /*<<< orphan*/  files_reflog_iterator_vtable ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct files_reflog_iterator* xcalloc (int,int) ; 

__attribute__((used)) static struct ref_iterator *reflog_iterator_begin(struct ref_store *ref_store,
						  const char *gitdir)
{
	struct dir_iterator *diter;
	struct files_reflog_iterator *iter;
	struct ref_iterator *ref_iterator;
	struct strbuf sb = STRBUF_INIT;

	strbuf_addf(&sb, "%s/logs", gitdir);

	diter = dir_iterator_begin(sb.buf, 0);
	if (!diter) {
		strbuf_release(&sb);
		return empty_ref_iterator_begin();
	}

	iter = xcalloc(1, sizeof(*iter));
	ref_iterator = &iter->base;

	base_ref_iterator_init(ref_iterator, &files_reflog_iterator_vtable, 0);
	iter->dir_iterator = diter;
	iter->ref_store = ref_store;
	strbuf_release(&sb);

	return ref_iterator;
}