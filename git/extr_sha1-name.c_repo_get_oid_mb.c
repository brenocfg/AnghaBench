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
struct strbuf {char const* buf; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct commit_list {TYPE_2__* item; scalar_t__ next; } ;
struct commit {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit* lookup_commit_reference_gently (struct repository*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 struct commit_list* repo_get_merge_bases (struct repository*,struct commit*,struct commit*) ; 
 int repo_get_oid (struct repository*,char const*,struct object_id*) ; 
 int repo_get_oid_committish (struct repository*,char const*,struct object_id*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strstr (char const*,char*) ; 

int repo_get_oid_mb(struct repository *r,
		    const char *name,
		    struct object_id *oid)
{
	struct commit *one, *two;
	struct commit_list *mbs;
	struct object_id oid_tmp;
	const char *dots;
	int st;

	dots = strstr(name, "...");
	if (!dots)
		return repo_get_oid(r, name, oid);
	if (dots == name)
		st = repo_get_oid(r, "HEAD", &oid_tmp);
	else {
		struct strbuf sb;
		strbuf_init(&sb, dots - name);
		strbuf_add(&sb, name, dots - name);
		st = repo_get_oid_committish(r, sb.buf, &oid_tmp);
		strbuf_release(&sb);
	}
	if (st)
		return st;
	one = lookup_commit_reference_gently(r, &oid_tmp, 0);
	if (!one)
		return -1;

	if (repo_get_oid_committish(r, dots[3] ? (dots + 3) : "HEAD", &oid_tmp))
		return -1;
	two = lookup_commit_reference_gently(r, &oid_tmp, 0);
	if (!two)
		return -1;
	mbs = repo_get_merge_bases(r, one, two);
	if (!mbs || mbs->next)
		st = -1;
	else {
		st = 0;
		oidcpy(oid, &mbs->item->object.oid);
	}
	free_commit_list(mbs);
	return st;
}