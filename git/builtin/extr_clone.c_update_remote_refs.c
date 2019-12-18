#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct transport {int /*<<< orphan*/  progress; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct ref {TYPE_1__* peer_ref; } ;
struct check_connected_options {int check_refs_only; int /*<<< orphan*/  progress; struct transport* transport; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct check_connected_options CHECK_CONNECTED_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_connected (int /*<<< orphan*/ ,struct ref const**,struct check_connected_options*) ; 
 scalar_t__ create_symref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  iterate_ref_map ; 
 int /*<<< orphan*/  option_bare ; 
 int /*<<< orphan*/  option_no_tags ; 
 scalar_t__ option_single_branch ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_followtags (struct ref const*,char const*) ; 
 int /*<<< orphan*/  write_remote_refs (struct ref const*) ; 

__attribute__((used)) static void update_remote_refs(const struct ref *refs,
			       const struct ref *mapped_refs,
			       const struct ref *remote_head_points_at,
			       const char *branch_top,
			       const char *msg,
			       struct transport *transport,
			       int check_connectivity,
			       int check_refs_only)
{
	const struct ref *rm = mapped_refs;

	if (check_connectivity) {
		struct check_connected_options opt = CHECK_CONNECTED_INIT;

		opt.transport = transport;
		opt.progress = transport->progress;
		opt.check_refs_only = !!check_refs_only;

		if (check_connected(iterate_ref_map, &rm, &opt))
			die(_("remote did not send all necessary objects"));
	}

	if (refs) {
		write_remote_refs(mapped_refs);
		if (option_single_branch && !option_no_tags)
			write_followtags(refs, msg);
	}

	if (remote_head_points_at && !option_bare) {
		struct strbuf head_ref = STRBUF_INIT;
		strbuf_addstr(&head_ref, branch_top);
		strbuf_addstr(&head_ref, "HEAD");
		if (create_symref(head_ref.buf,
				  remote_head_points_at->peer_ref->name,
				  msg) < 0)
			die(_("unable to update %s"), head_ref.buf);
		strbuf_release(&head_ref);
	}
}