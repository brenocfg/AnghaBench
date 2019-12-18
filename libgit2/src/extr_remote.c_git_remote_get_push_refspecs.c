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
typedef  int /*<<< orphan*/  git_strarray ;
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int copy_refspecs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int git_remote_get_push_refspecs(git_strarray *array, const git_remote *remote)
{
	return copy_refspecs(array, remote, true);
}