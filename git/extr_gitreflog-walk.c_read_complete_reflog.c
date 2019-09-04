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
struct complete_reflogs {scalar_t__ nr; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 int /*<<< orphan*/  for_each_reflog_ent (char const*,int /*<<< orphan*/ ,struct complete_reflogs*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  read_one_reflog ; 
 void* resolve_refdup (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct complete_reflogs* xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 
 char* xstrfmt (char*,char const*) ; 

__attribute__((used)) static struct complete_reflogs *read_complete_reflog(const char *ref)
{
	struct complete_reflogs *reflogs =
		xcalloc(1, sizeof(struct complete_reflogs));
	reflogs->ref = xstrdup(ref);
	for_each_reflog_ent(ref, read_one_reflog, reflogs);
	if (reflogs->nr == 0) {
		const char *name;
		void *name_to_free;
		name = name_to_free = resolve_refdup(ref, RESOLVE_REF_READING,
						     NULL, NULL);
		if (name) {
			for_each_reflog_ent(name, read_one_reflog, reflogs);
			free(name_to_free);
		}
	}
	if (reflogs->nr == 0) {
		char *refname = xstrfmt("refs/%s", ref);
		for_each_reflog_ent(refname, read_one_reflog, reflogs);
		if (reflogs->nr == 0) {
			free(refname);
			refname = xstrfmt("refs/heads/%s", ref);
			for_each_reflog_ent(refname, read_one_reflog, reflogs);
		}
		free(refname);
	}
	return reflogs;
}