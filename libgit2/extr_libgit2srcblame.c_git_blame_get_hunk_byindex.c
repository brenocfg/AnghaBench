#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  const git_blame_hunk ;
struct TYPE_4__ {int /*<<< orphan*/  hunks; } ;
typedef  TYPE_1__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ git_vector_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const git_blame_hunk *git_blame_get_hunk_byindex(git_blame *blame, uint32_t index)
{
	assert(blame);
	return (git_blame_hunk*)git_vector_get(&blame->hunks, index);
}