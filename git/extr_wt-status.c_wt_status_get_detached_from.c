#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct wt_status_state {int detached_at; struct object_id detached_oid; void* detached_from; } ;
struct repository {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct grab_1st_switch_cbdata {TYPE_2__ buf; struct object_id noid; } ;
struct TYPE_4__ {struct object_id oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int dwim_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,char**) ; 
 char const* find_unique_abbrev (struct object_id*,int /*<<< orphan*/ ) ; 
 scalar_t__ for_each_reflog_ent_reverse (char*,int /*<<< orphan*/ ,struct grab_1st_switch_cbdata*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_oid (char*,struct object_id*) ; 
 int /*<<< orphan*/  grab_1st_switch ; 
 struct commit* lookup_commit_reference_gently (struct repository*,struct object_id*,int) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 scalar_t__ oideq (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_2__*) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static void wt_status_get_detached_from(struct repository *r,
					struct wt_status_state *state)
{
	struct grab_1st_switch_cbdata cb;
	struct commit *commit;
	struct object_id oid;
	char *ref = NULL;

	strbuf_init(&cb.buf, 0);
	if (for_each_reflog_ent_reverse("HEAD", grab_1st_switch, &cb) <= 0) {
		strbuf_release(&cb.buf);
		return;
	}

	if (dwim_ref(cb.buf.buf, cb.buf.len, &oid, &ref) == 1 &&
	    /* sha1 is a commit? match without further lookup */
	    (oideq(&cb.noid, &oid) ||
	     /* perhaps sha1 is a tag, try to dereference to a commit */
	     ((commit = lookup_commit_reference_gently(r, &oid, 1)) != NULL &&
	      oideq(&cb.noid, &commit->object.oid)))) {
		const char *from = ref;
		if (!skip_prefix(from, "refs/tags/", &from))
			skip_prefix(from, "refs/remotes/", &from);
		state->detached_from = xstrdup(from);
	} else
		state->detached_from =
			xstrdup(find_unique_abbrev(&cb.noid, DEFAULT_ABBREV));
	oidcpy(&state->detached_oid, &cb.noid);
	state->detached_at = !get_oid("HEAD", &oid) &&
			     oideq(&oid, &state->detached_oid);

	free(ref);
	strbuf_release(&cb.buf);
}