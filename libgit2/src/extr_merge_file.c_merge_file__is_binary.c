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
struct TYPE_3__ {size_t size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_merge_file_input ;

/* Variables and functions */
 size_t GIT_MERGE_FILE_BINARY_SIZE ; 
 size_t GIT_XDIFF_MAX_SIZE ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static bool merge_file__is_binary(const git_merge_file_input *file)
{
	size_t len = file ? file->size : 0;

	if (len > GIT_XDIFF_MAX_SIZE)
		return true;
	if (len > GIT_MERGE_FILE_BINARY_SIZE)
		len = GIT_MERGE_FILE_BINARY_SIZE;

	return len ? (memchr(file->ptr, 0, len) != NULL) : false;
}