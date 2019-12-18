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
typedef  int /*<<< orphan*/  git_status_cb ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int git_status_foreach_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

int git_status_foreach(git_repository *repo, git_status_cb cb, void *payload)
{
	return git_status_foreach_ext(repo, NULL, cb, payload);
}