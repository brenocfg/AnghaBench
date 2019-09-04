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
struct object_id {int dummy; } ;
struct commit_list {TYPE_2__* item; scalar_t__ next; } ;
struct commit {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* get_merge_bases (struct commit*,struct commit*) ; 
 int get_oid (char const*,struct object_id*) ; 
 int get_oid_committish (char const*,struct object_id*) ; 
 struct commit* lookup_commit_reference_gently (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strstr (char const*,char*) ; 
 int /*<<< orphan*/  the_repository ; 

int get_oid_mb(const char *name, struct object_id *oid)
{
	struct commit *one, *two;
	struct commit_list *mbs;
	struct object_id oid_tmp;
	const char *dots;
	int st;

	dots = strstr(name, "...");
	if (!dots)
		return get_oid(name, oid);
	if (dots == name)
		st = get_oid("HEAD", &oid_tmp);
	else {
		struct strbuf sb;
		strbuf_init(&sb, dots - name);
		strbuf_add(&sb, name, dots - name);
		st = get_oid_committish(sb.buf, &oid_tmp);
		strbuf_release(&sb);
	}
	if (st)
		return st;
	one = lookup_commit_reference_gently(the_repository, &oid_tmp, 0);
	if (!one)
		return -1;

	if (get_oid_committish(dots[3] ? (dots + 3) : "HEAD", &oid_tmp))
		return -1;
	two = lookup_commit_reference_gently(the_repository, &oid_tmp, 0);
	if (!two)
		return -1;
	mbs = get_merge_bases(one, two);
	if (!mbs || mbs->next)
		st = -1;
	else {
		st = 0;
		oidcpy(oid, &mbs->item->object.oid);
	}
	free_commit_list(mbs);
	return st;
}