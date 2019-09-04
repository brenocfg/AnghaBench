#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; int /*<<< orphan*/  _cmp; int /*<<< orphan*/  contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git__tsort (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ git_vector_is_sorted (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_set_sorted (TYPE_1__*,int) ; 

void git_vector_sort(git_vector *v)
{
	assert(v);

	if (git_vector_is_sorted(v) || !v->_cmp)
		return;

	if (v->length > 1)
		git__tsort(v->contents, v->length, v->_cmp);
	git_vector_set_sorted(v, 1);
}