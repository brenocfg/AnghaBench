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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void git_vector_swap(git_vector *a, git_vector *b)
{
	git_vector t;

	assert(a && b);

	if (a != b) {
		memcpy(&t, a, sizeof(t));
		memcpy(a, b, sizeof(t));
		memcpy(b, &t, sizeof(t));
	}
}