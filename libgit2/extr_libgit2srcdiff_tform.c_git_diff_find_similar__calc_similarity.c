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
 int git_hashsig_compare (void*,void*) ; 

int git_diff_find_similar__calc_similarity(
	int *score, void *siga, void *sigb, void *payload)
{
	int error;

	GIT_UNUSED(payload);
	error = git_hashsig_compare(siga, sigb);
	if (error < 0)
		return error;

	*score = error;
	return 0;
}