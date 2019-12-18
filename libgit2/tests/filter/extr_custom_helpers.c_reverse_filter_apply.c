#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* git_filter_source ;
typedef  void* const git_filter ;
struct TYPE_5__ {int size; scalar_t__ ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void* const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__strncmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_buf_grow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  git_filter_source_path (void* const*) ; 

int reverse_filter_apply(
	git_filter     *self,
	void          **payload,
	git_buf        *to,
	const git_buf  *from,
	const git_filter_source *source)
{
	const unsigned char *src = (const unsigned char *)from->ptr;
	const unsigned char *end = src + from->size;
	unsigned char *dst;

	GIT_UNUSED(self); GIT_UNUSED(payload); GIT_UNUSED(source);

	/* verify that attribute path match worked as expected */
	cl_assert_equal_i(
		0, git__strncmp("hero", git_filter_source_path(source), 4));

	if (!from->size)
		return 0;

	cl_git_pass(git_buf_grow(to, from->size));

	dst = (unsigned char *)to->ptr + from->size - 1;

	while (src < end)
		*dst-- = *src++;

	to->size = from->size;

	return 0;
}