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

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int git_repository_init (int /*<<< orphan*/ **,char const*,int) ; 

__attribute__((used)) static int default_repository_create(git_repository **out, const char *path, int bare, void *payload)
{
	GIT_UNUSED(payload);

	return git_repository_init(out, path, bare);
}