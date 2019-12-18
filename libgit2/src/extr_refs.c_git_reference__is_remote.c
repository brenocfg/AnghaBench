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
 int /*<<< orphan*/  GIT_REFS_REMOTES_DIR ; 
 scalar_t__ git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 

int git_reference__is_remote(const char *ref_name)
{
	return git__prefixcmp(ref_name, GIT_REFS_REMOTES_DIR) == 0;
}