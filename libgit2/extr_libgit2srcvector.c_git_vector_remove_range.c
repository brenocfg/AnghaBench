#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t length; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ git__add_sizet_overflow (size_t*,size_t,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int git_vector_remove_range(git_vector *v, size_t idx, size_t remove_len)
{
	size_t new_length = v->length - remove_len;
	size_t end_idx = 0;
	
	assert(remove_len > 0);

	if (git__add_sizet_overflow(&end_idx, idx, remove_len))
		assert(0);

	assert(end_idx <= v->length);

	if (end_idx < v->length)
		memmove(&v->contents[idx], &v->contents[end_idx],
			sizeof(void *) * (v->length - end_idx));

	memset(&v->contents[new_length], 0, sizeof(void *) * remove_len);

	v->length = new_length;
	return 0;
}