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
struct blame_origin {struct blame_origin* next; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 struct blame_origin* blame_origin_incref (struct blame_origin*) ; 
 void* get_blame_suspects (struct commit*) ; 
 struct blame_origin* make_origin (struct commit*,char const*) ; 
 int /*<<< orphan*/  set_blame_suspects (struct commit*,struct blame_origin*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static struct blame_origin *get_origin(struct commit *commit, const char *path)
{
	struct blame_origin *o, *l;

	for (o = get_blame_suspects(commit), l = NULL; o; l = o, o = o->next) {
		if (!strcmp(o->path, path)) {
			/* bump to front */
			if (l) {
				l->next = o->next;
				o->next = get_blame_suspects(commit);
				set_blame_suspects(commit, o);
			}
			return blame_origin_incref(o);
		}
	}
	return make_origin(commit, path);
}