#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  allow_textconv; int /*<<< orphan*/  textconv_set_via_cmdline; } ;
struct TYPE_4__ {TYPE_1__ flags; int /*<<< orphan*/  file; } ;
struct rev_info {TYPE_2__ diffopt; } ;
struct object_id {int dummy; } ;
struct object_context {int /*<<< orphan*/  path; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_OID_RECORD_PATH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid_with_context (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct object_id*,struct object_context*) ; 
 int stream_blob_to_fd (int,struct object_id const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  textconv_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,int,char**,unsigned long*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  write_or_die (int,char*,unsigned long) ; 

__attribute__((used)) static int show_blob_object(const struct object_id *oid, struct rev_info *rev, const char *obj_name)
{
	struct object_id oidc;
	struct object_context obj_context;
	char *buf;
	unsigned long size;

	fflush(rev->diffopt.file);
	if (!rev->diffopt.flags.textconv_set_via_cmdline ||
	    !rev->diffopt.flags.allow_textconv)
		return stream_blob_to_fd(1, oid, NULL, 0);

	if (get_oid_with_context(the_repository, obj_name,
				 GET_OID_RECORD_PATH,
				 &oidc, &obj_context))
		die(_("not a valid object name %s"), obj_name);
	if (!obj_context.path ||
	    !textconv_object(the_repository, obj_context.path,
			     obj_context.mode, &oidc, 1, &buf, &size)) {
		free(obj_context.path);
		return stream_blob_to_fd(1, oid, NULL, 0);
	}

	if (!buf)
		die(_("git show %s: bad file"), obj_name);

	write_or_die(1, buf, size);
	free(obj_context.path);
	return 0;
}