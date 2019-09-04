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
typedef  int /*<<< orphan*/  git_remote ;

/* Variables and functions */
 int git_remote_create_with_opts (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 

int git_remote_create_detached(git_remote **out, const char *url)
{
	return git_remote_create_with_opts(out, url, NULL);
}