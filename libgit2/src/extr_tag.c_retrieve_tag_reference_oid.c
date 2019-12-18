#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFS_TAGS_DIR ; 
 scalar_t__ git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int retrieve_tag_reference_oid(
	git_oid *oid,
	git_buf *ref_name_out,
	git_repository *repo,
	const char *tag_name)
{
	if (git_buf_joinpath(ref_name_out, GIT_REFS_TAGS_DIR, tag_name) < 0)
		return -1;

	return git_reference_name_to_id(oid, repo, ref_name_out->ptr);
}