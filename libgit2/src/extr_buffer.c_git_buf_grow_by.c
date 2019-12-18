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
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_buf__oom ; 
 int git_buf_try_grow (TYPE_1__*,size_t,int) ; 

int git_buf_grow_by(git_buf *buffer, size_t additional_size)
{
	size_t newsize;

	if (GIT_ADD_SIZET_OVERFLOW(&newsize, buffer->size, additional_size)) {
		buffer->ptr = git_buf__oom;
		return -1;
	}

	return git_buf_try_grow(buffer, newsize, true);
}