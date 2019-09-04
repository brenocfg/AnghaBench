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
struct TYPE_4__ {size_t length; scalar_t__ (* _cmp ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  git_vector_is_sorted (TYPE_1__ const*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_vector_verify_sorted(const git_vector *v)
{
	size_t i;

	if (!git_vector_is_sorted(v))
		return -1;

	for (i = 1; i < v->length; ++i) {
		if (v->_cmp(v->contents[i - 1], v->contents[i]) > 0)
			return -1;
	}

	return 0;
}