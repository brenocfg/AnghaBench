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
struct commit {int dummy; } ;
struct blame_origin {int refcnt; int /*<<< orphan*/  next; struct commit* commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct blame_origin*,char const*,char const*) ; 
 int /*<<< orphan*/  get_blame_suspects (struct commit*) ; 
 int /*<<< orphan*/  set_blame_suspects (struct commit*,struct blame_origin*) ; 

__attribute__((used)) static struct blame_origin *make_origin(struct commit *commit, const char *path)
{
	struct blame_origin *o;
	FLEX_ALLOC_STR(o, path, path);
	o->commit = commit;
	o->refcnt = 1;
	o->next = get_blame_suspects(commit);
	set_blame_suspects(commit, o);
	return o;
}