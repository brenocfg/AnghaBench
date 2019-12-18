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
typedef  int /*<<< orphan*/  git_indexer ;

/* Variables and functions */
 int /*<<< orphan*/  _stats ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexer_append (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int foreach_cb(void *buf, size_t len, void *payload)
{
	git_indexer *idx = (git_indexer *) payload;
	cl_git_pass(git_indexer_append(idx, buf, len, &_stats));
	return 0;
}