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
struct strbuf {char* buf; } ;
struct ref {int /*<<< orphan*/ * peer_ref; int /*<<< orphan*/  new_oid; scalar_t__ forced_update; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; scalar_t__ deletion; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_ref_status (char,char*,struct ref*,int /*<<< orphan*/ *,char const*,int,int) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (struct strbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void print_ok_ref_status(struct ref *ref, int porcelain, int summary_width)
{
	if (ref->deletion)
		print_ref_status('-', "[deleted]", ref, NULL, NULL,
				 porcelain, summary_width);
	else if (is_null_oid(&ref->old_oid))
		print_ref_status('*',
			(starts_with(ref->name, "refs/tags/") ? "[new tag]" :
			"[new branch]"),
			ref, ref->peer_ref, NULL, porcelain, summary_width);
	else {
		struct strbuf quickref = STRBUF_INIT;
		char type;
		const char *msg;

		strbuf_add_unique_abbrev(&quickref, &ref->old_oid,
					 DEFAULT_ABBREV);
		if (ref->forced_update) {
			strbuf_addstr(&quickref, "...");
			type = '+';
			msg = "forced update";
		} else {
			strbuf_addstr(&quickref, "..");
			type = ' ';
			msg = NULL;
		}
		strbuf_add_unique_abbrev(&quickref, &ref->new_oid,
					 DEFAULT_ABBREV);

		print_ref_status(type, quickref.buf, ref, ref->peer_ref, msg,
				 porcelain, summary_width);
		strbuf_release(&quickref);
	}
}