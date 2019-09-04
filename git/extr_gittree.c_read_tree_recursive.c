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
struct tree {int dummy; } ;
struct strbuf {int dummy; } ;
struct repository {int dummy; } ;
struct pathspec {int dummy; } ;
typedef  int /*<<< orphan*/  read_tree_fn_t ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int read_tree_1 (struct repository*,struct tree*,struct strbuf*,int,struct pathspec const*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int read_tree_recursive(struct repository *r,
			struct tree *tree,
			const char *base, int baselen,
			int stage, const struct pathspec *pathspec,
			read_tree_fn_t fn, void *context)
{
	struct strbuf sb = STRBUF_INIT;
	int ret;

	strbuf_add(&sb, base, baselen);
	ret = read_tree_1(r, tree, &sb, stage, pathspec, fn, context);
	strbuf_release(&sb);
	return ret;
}