#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_filebuf ;
struct TYPE_3__ {char* ref_name; int /*<<< orphan*/  remote_url; scalar_t__ is_merge; int /*<<< orphan*/  oid; } ;
typedef  TYPE_1__ git_fetchhead_ref ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  GIT_REFS_TAGS_DIR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git__prefixcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strcmp (char*,int /*<<< orphan*/ ) ; 
 int git_filebuf_printf (int /*<<< orphan*/ *,char*,char*,char*,...) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fetchhead_ref_write(
	git_filebuf *file,
	git_fetchhead_ref *fetchhead_ref)
{
	char oid[GIT_OID_HEXSZ + 1];
	const char *type, *name;
	int head = 0;

	assert(file && fetchhead_ref);

	git_oid_fmt(oid, &fetchhead_ref->oid);
	oid[GIT_OID_HEXSZ] = '\0';

	if (git__prefixcmp(fetchhead_ref->ref_name, GIT_REFS_HEADS_DIR) == 0) {
		type = "branch ";
		name = fetchhead_ref->ref_name + strlen(GIT_REFS_HEADS_DIR);
	} else if(git__prefixcmp(fetchhead_ref->ref_name,
		GIT_REFS_TAGS_DIR) == 0) {
		type = "tag ";
		name = fetchhead_ref->ref_name + strlen(GIT_REFS_TAGS_DIR);
	} else if (!git__strcmp(fetchhead_ref->ref_name, GIT_HEAD_FILE)) {
		head = 1;
	} else {
		type = "";
		name = fetchhead_ref->ref_name;
	}

	if (head)
		return git_filebuf_printf(file, "%s\t\t%s\n", oid, fetchhead_ref->remote_url);

	return git_filebuf_printf(file, "%s\t%s\t%s'%s' of %s\n",
		oid,
		(fetchhead_ref->is_merge) ? "" : "not-for-merge",
		type,
		name,
		fetchhead_ref->remote_url);
}