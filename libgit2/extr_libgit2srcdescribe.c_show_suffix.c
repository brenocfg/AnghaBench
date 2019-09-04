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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int find_unique_abbrev_size (int*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_buf_put (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_oid_fmt (char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int show_suffix(
	git_buf *buf,
	int depth,
	git_repository *repo,
	const git_oid* id,
	unsigned int abbrev_size)
{
	int error, size = 0;

	char hex_oid[GIT_OID_HEXSZ];

	if ((error = find_unique_abbrev_size(&size, repo, id, abbrev_size)) < 0)
		return error;

	git_oid_fmt(hex_oid, id);

	git_buf_printf(buf, "-%d-g", depth);

	git_buf_put(buf, hex_oid, size);

	return git_buf_oom(buf) ? -1 : 0;
}