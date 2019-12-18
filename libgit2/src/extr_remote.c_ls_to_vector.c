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
typedef  int /*<<< orphan*/  git_vector ;
typedef  int /*<<< orphan*/  git_remote_head ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 scalar_t__ git_remote_ls (int /*<<< orphan*/  const***,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remote_head_cmp ; 

__attribute__((used)) static int ls_to_vector(git_vector *out, git_remote *remote)
{
	git_remote_head **heads;
	size_t heads_len, i;

	if (git_remote_ls((const git_remote_head ***)&heads, &heads_len, remote) < 0)
		return -1;

	if (git_vector_init(out, heads_len, remote_head_cmp) < 0)
		return -1;

	for (i = 0; i < heads_len; i++) {
		if (git_vector_insert(out, heads[i]) < 0)
			return -1;
	}

	return 0;
}