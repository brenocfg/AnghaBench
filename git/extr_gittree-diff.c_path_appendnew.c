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
struct strbuf {int len; char const* buf; } ;
struct object_id {int dummy; } ;
struct combine_diff_path {char* path; unsigned int mode; int /*<<< orphan*/  oid; int /*<<< orphan*/ * parent; struct combine_diff_path* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (struct combine_diff_path*) ; 
 size_t combine_diff_path_size (int,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 struct object_id const null_oid ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 size_t st_add (int,int) ; 
 struct combine_diff_path* xmalloc (size_t) ; 

__attribute__((used)) static struct combine_diff_path *path_appendnew(struct combine_diff_path *last,
	int nparent, const struct strbuf *base, const char *path, int pathlen,
	unsigned mode, const struct object_id *oid)
{
	struct combine_diff_path *p;
	size_t len = st_add(base->len, pathlen);
	size_t alloclen = combine_diff_path_size(nparent, len);

	/* if last->next is !NULL - it is a pre-allocated memory, we can reuse */
	p = last->next;
	if (p && (alloclen > (intptr_t)p->next)) {
		FREE_AND_NULL(p);
	}

	if (!p) {
		p = xmalloc(alloclen);

		/*
		 * until we go to it next round, .next holds how many bytes we
		 * allocated (for faster realloc - we don't need copying old data).
		 */
		p->next = (struct combine_diff_path *)(intptr_t)alloclen;
	}

	last->next = p;

	p->path = (char *)&(p->parent[nparent]);
	memcpy(p->path, base->buf, base->len);
	memcpy(p->path + base->len, path, pathlen);
	p->path[len] = 0;
	p->mode = mode;
	oidcpy(&p->oid, oid ? oid : &null_oid);

	return p;
}