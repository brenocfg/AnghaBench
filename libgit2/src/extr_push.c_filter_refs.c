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
typedef  int /*<<< orphan*/  git_remote_head ;
struct TYPE_4__ {int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ git_remote ;

/* Variables and functions */
 scalar_t__ git_remote_ls (int /*<<< orphan*/  const***,size_t*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_insert (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int filter_refs(git_remote *remote)
{
	const git_remote_head **heads;
	size_t heads_len, i;

	git_vector_clear(&remote->refs);

	if (git_remote_ls(&heads, &heads_len, remote) < 0)
		return -1;

	for (i = 0; i < heads_len; i++) {
		if (git_vector_insert(&remote->refs, (void *)heads[i]) < 0)
			return -1;
	}

	return 0;
}