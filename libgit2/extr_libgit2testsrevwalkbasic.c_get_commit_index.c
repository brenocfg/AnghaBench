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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int commit_count ; 
 int /*<<< orphan*/ * commit_ids ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_commit_index(git_oid *raw_oid)
{
	int i;
	char oid[GIT_OID_HEXSZ];

	git_oid_fmt(oid, raw_oid);

	for (i = 0; i < commit_count; ++i)
		if (memcmp(oid, commit_ids[i], GIT_OID_HEXSZ) == 0)
			return i;

	return -1;
}