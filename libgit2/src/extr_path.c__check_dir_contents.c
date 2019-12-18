#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 scalar_t__ git_buf_joinpath (TYPE_1__*,char const*,char const*) ; 
 size_t git_buf_len (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_1__*,size_t) ; 
 scalar_t__ git_buf_try_grow (TYPE_1__*,size_t,int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static bool _check_dir_contents(
	git_buf *dir,
	const char *sub,
	bool (*predicate)(const char *))
{
	bool result;
	size_t dir_size = git_buf_len(dir);
	size_t sub_size = strlen(sub);
	size_t alloc_size;

	/* leave base valid even if we could not make space for subdir */
	if (GIT_ADD_SIZET_OVERFLOW(&alloc_size, dir_size, sub_size) ||
		GIT_ADD_SIZET_OVERFLOW(&alloc_size, alloc_size, 2) ||
		git_buf_try_grow(dir, alloc_size, false) < 0)
		return false;

	/* save excursion */
	if (git_buf_joinpath(dir, dir->ptr, sub) < 0)
		return false;

	result = predicate(dir->ptr);

	/* restore path */
	git_buf_truncate(dir, dir_size);
	return result;
}