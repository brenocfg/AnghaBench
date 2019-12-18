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
typedef  int /*<<< orphan*/  git_clone_options ;

/* Variables and functions */
 int git__clone (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int git_clone(
	git_repository **out,
	const char *url,
	const char *local_path,
	const git_clone_options *_options)
{
	return git__clone(out, url, local_path, _options, 0);
}