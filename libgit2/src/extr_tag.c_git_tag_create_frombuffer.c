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

/* Variables and functions */
 int git_tag_create_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int) ; 

int git_tag_create_frombuffer(git_oid *oid, git_repository *repo, const char *buffer, int allow_ref_overwrite)
{
	return git_tag_create_from_buffer(oid, repo, buffer, allow_ref_overwrite);
}