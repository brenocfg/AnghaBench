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
struct worktree {int /*<<< orphan*/  head_oid; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_unique_abbrev (int /*<<< orphan*/ *,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void measure_widths(struct worktree **wt, int *abbrev, int *maxlen)
{
	int i;

	for (i = 0; wt[i]; i++) {
		int sha1_len;
		int path_len = strlen(wt[i]->path);

		if (path_len > *maxlen)
			*maxlen = path_len;
		sha1_len = strlen(find_unique_abbrev(&wt[i]->head_oid, *abbrev));
		if (sha1_len > *abbrev)
			*abbrev = sha1_len;
	}
}