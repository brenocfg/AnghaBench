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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int refs_foreach_cancel_cb(git_reference *reference, void *payload)
{
	int *cancel_after = payload;

	git_reference_free(reference);

	if (!*cancel_after)
		return -333;
	(*cancel_after)--;
	return 0;
}