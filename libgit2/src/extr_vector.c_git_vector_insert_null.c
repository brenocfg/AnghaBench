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
struct TYPE_4__ {size_t length; size_t _alloc_size; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC_ADD (size_t*,size_t,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ resize_vector (TYPE_1__*,size_t) ; 

int git_vector_insert_null(git_vector *v, size_t idx, size_t insert_len)
{
	size_t new_length;

	assert(insert_len > 0 && idx <= v->length);

	GIT_ERROR_CHECK_ALLOC_ADD(&new_length, v->length, insert_len);

	if (new_length > v->_alloc_size && resize_vector(v, new_length) < 0)
		return -1;

	memmove(&v->contents[idx + insert_len], &v->contents[idx],
		sizeof(void *) * (v->length - idx));
	memset(&v->contents[idx], 0, sizeof(void *) * insert_len);

	v->length = new_length;
	return 0;
}