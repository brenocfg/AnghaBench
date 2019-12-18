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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_REFS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  errors_found ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int fsck_head_link(const char *head_ref_name,
			  const char **head_points_at,
			  struct object_id *head_oid)
{
	int null_is_error = 0;

	if (verbose)
		fprintf_ln(stderr, _("Checking %s link"), head_ref_name);

	*head_points_at = resolve_ref_unsafe(head_ref_name, 0, head_oid, NULL);
	if (!*head_points_at) {
		errors_found |= ERROR_REFS;
		return error(_("invalid %s"), head_ref_name);
	}
	if (!strcmp(*head_points_at, head_ref_name))
		/* detached HEAD */
		null_is_error = 1;
	else if (!starts_with(*head_points_at, "refs/heads/")) {
		errors_found |= ERROR_REFS;
		return error(_("%s points to something strange (%s)"),
			     head_ref_name, *head_points_at);
	}
	if (is_null_oid(head_oid)) {
		if (null_is_error) {
			errors_found |= ERROR_REFS;
			return error(_("%s: detached HEAD points at nothing"),
				     head_ref_name);
		}
		fprintf_ln(stderr,
			   _("notice: %s points to an unborn branch (%s)"),
			   head_ref_name, *head_points_at + 11);
	}
	return 0;
}