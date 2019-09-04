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
typedef  int /*<<< orphan*/  git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  expected_ref ;

/* Variables and functions */
 int /*<<< orphan*/  git_remote_ls (int /*<<< orphan*/  const***,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify_remote_refs (int /*<<< orphan*/  const**,size_t,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void verify_refs(git_remote *remote, expected_ref expected_refs[], size_t expected_refs_len)
{
	const git_remote_head **actual_refs;
	size_t actual_refs_len;

	git_remote_ls(&actual_refs, &actual_refs_len, remote);
	verify_remote_refs(actual_refs, actual_refs_len, expected_refs, expected_refs_len);
}