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
typedef  int /*<<< orphan*/  git_diff_hunk ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int hunk_skip_odds_cb(const git_diff_hunk *hunk, void *payload)
{
	int *count = (int *)payload;
	GIT_UNUSED(hunk);

	return ((*count)++ % 2 == 1);
}