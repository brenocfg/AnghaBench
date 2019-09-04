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
struct warn_if_dangling_data {char* msg_fmt; int /*<<< orphan*/  fp; int /*<<< orphan*/  refnames; scalar_t__ refname; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strcmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  string_list_has_string (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int warn_if_dangling_symref(const char *refname, const struct object_id *oid,
				   int flags, void *cb_data)
{
	struct warn_if_dangling_data *d = cb_data;
	const char *resolves_to;

	if (!(flags & REF_ISSYMREF))
		return 0;

	resolves_to = resolve_ref_unsafe(refname, 0, NULL, NULL);
	if (!resolves_to
	    || (d->refname
		? strcmp(resolves_to, d->refname)
		: !string_list_has_string(d->refnames, resolves_to))) {
		return 0;
	}

	fprintf(d->fp, d->msg_fmt, refname);
	fputc('\n', d->fp);
	return 0;
}