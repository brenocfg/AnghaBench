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
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *****) ; 
 int /*<<< orphan*/ ***** pending_completions ; 

__attribute__((used)) static void readline_free_completions(void)
{
	int i;
	if (pending_completions == NULL)
		return;
	for (i = 0; pending_completions[i]; i++)
		os_free(pending_completions[i]);
	os_free(pending_completions);
	pending_completions = NULL;
}