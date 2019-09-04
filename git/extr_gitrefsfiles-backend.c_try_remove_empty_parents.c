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
struct strbuf {char* buf; int len; } ;
struct files_ref_store {int dummy; } ;

/* Variables and functions */
 unsigned int REMOVE_EMPTY_PARENTS_REF ; 
 unsigned int REMOVE_EMPTY_PARENTS_REFLOG ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  files_ref_path (struct files_ref_store*,struct strbuf*,char*) ; 
 int /*<<< orphan*/  files_reflog_path (struct files_ref_store*,struct strbuf*,char*) ; 
 scalar_t__ rmdir (char*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

__attribute__((used)) static void try_remove_empty_parents(struct files_ref_store *refs,
				     const char *refname,
				     unsigned int flags)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	char *p, *q;
	int i;

	strbuf_addstr(&buf, refname);
	p = buf.buf;
	for (i = 0; i < 2; i++) { /* refs/{heads,tags,...}/ */
		while (*p && *p != '/')
			p++;
		/* tolerate duplicate slashes; see check_refname_format() */
		while (*p == '/')
			p++;
	}
	q = buf.buf + buf.len;
	while (flags & (REMOVE_EMPTY_PARENTS_REF | REMOVE_EMPTY_PARENTS_REFLOG)) {
		while (q > p && *q != '/')
			q--;
		while (q > p && *(q-1) == '/')
			q--;
		if (q == p)
			break;
		strbuf_setlen(&buf, q - buf.buf);

		strbuf_reset(&sb);
		files_ref_path(refs, &sb, buf.buf);
		if ((flags & REMOVE_EMPTY_PARENTS_REF) && rmdir(sb.buf))
			flags &= ~REMOVE_EMPTY_PARENTS_REF;

		strbuf_reset(&sb);
		files_reflog_path(refs, &sb, buf.buf);
		if ((flags & REMOVE_EMPTY_PARENTS_REFLOG) && rmdir(sb.buf))
			flags &= ~REMOVE_EMPTY_PARENTS_REFLOG;
	}
	strbuf_release(&buf);
	strbuf_release(&sb);
}