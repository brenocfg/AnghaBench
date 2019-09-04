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
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  git_hashsig_free (void*) ; 

void git_diff_find_similar__hashsig_free(void *sig, void *payload)
{
	GIT_UNUSED(payload);
	git_hashsig_free(sig);
}