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
struct wt_status {char const* prefix; int amend; char* reference; char const* index_file; int nowarn; int is_initial; int committable; int /*<<< orphan*/  ignore_submodule_arg; int /*<<< orphan*/  status_format; int /*<<< orphan*/  oid_commit; int /*<<< orphan*/ * fp; int /*<<< orphan*/  verbose; scalar_t__ relative_paths; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ amend ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  ignore_submodule_arg ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 int /*<<< orphan*/  status_format ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  wt_status_collect (struct wt_status*) ; 
 int /*<<< orphan*/  wt_status_collect_free_buffers (struct wt_status*) ; 
 int /*<<< orphan*/  wt_status_print (struct wt_status*) ; 

__attribute__((used)) static int run_status(FILE *fp, const char *index_file, const char *prefix, int nowarn,
		      struct wt_status *s)
{
	struct object_id oid;

	if (s->relative_paths)
		s->prefix = prefix;

	if (amend) {
		s->amend = 1;
		s->reference = "HEAD^1";
	}
	s->verbose = verbose;
	s->index_file = index_file;
	s->fp = fp;
	s->nowarn = nowarn;
	s->is_initial = get_oid(s->reference, &oid) ? 1 : 0;
	if (!s->is_initial)
		oidcpy(&s->oid_commit, &oid);
	s->status_format = status_format;
	s->ignore_submodule_arg = ignore_submodule_arg;

	wt_status_collect(s);
	wt_status_print(s);
	wt_status_collect_free_buffers(s);

	return s->committable;
}