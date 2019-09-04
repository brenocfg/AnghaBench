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

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,void*) ; 

__attribute__((used)) static int addall_cancel_at(
	const char *path, const char *matched_pathspec, void *payload)
{
	GIT_UNUSED(matched_pathspec);
	return !strcmp(path, payload) ? -123 : 0;
}