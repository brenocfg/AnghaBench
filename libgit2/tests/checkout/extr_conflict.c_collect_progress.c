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

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (size_t) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 

__attribute__((used)) static void collect_progress(
	const char *path,
	size_t completed_steps,
	size_t total_steps,
	void *payload)
{
	git_vector *paths = payload;

	GIT_UNUSED(completed_steps);
	GIT_UNUSED(total_steps);

	if (path == NULL)
		return;

	git_vector_insert(paths, strdup(path));
}