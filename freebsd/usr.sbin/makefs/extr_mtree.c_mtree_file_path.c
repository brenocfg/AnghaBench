#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sbuf {int dummy; } ;
struct TYPE_3__ {char* name; struct TYPE_3__* parent; } ;
typedef  TYPE_1__ fsnode ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int MAKEFS_MAX_TREE_DEPTH ; 
 int /*<<< orphan*/  errno ; 
 char* estrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static char *
mtree_file_path(fsnode *node)
{
	fsnode *pnode;
	struct sbuf *sb;
	char *res, *rp[MAKEFS_MAX_TREE_DEPTH];
	int depth;

	depth = 0;
	rp[depth] = node->name;
	for (pnode = node->parent; pnode && depth < MAKEFS_MAX_TREE_DEPTH - 1;
	     pnode = pnode->parent) {
		if (strcmp(pnode->name, ".") == 0)
			break;
		rp[++depth] = pnode->name;
	}
	
	sb = sbuf_new_auto();
	if (sb == NULL) {
		errno = ENOMEM;
		return (NULL);
	}
	while (depth > 0) {
		sbuf_cat(sb, rp[depth--]);
		sbuf_putc(sb, '/');
	}
	sbuf_cat(sb, rp[depth]);
	sbuf_finish(sb);
	res = estrdup(sbuf_data(sb));
	sbuf_delete(sb);
	if (res == NULL)
		errno = ENOMEM;
	return res;

}