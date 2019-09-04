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
struct TYPE_4__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_REFERENCE ; 
 int /*<<< orphan*/  GIT_SYMREF ; 
 unsigned int const git_buf_len (TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *loose_parse_symbolic(git_buf *file_content)
{
	const unsigned int header_len = (unsigned int)strlen(GIT_SYMREF);
	const char *refname_start;

	refname_start = (const char *)file_content->ptr;

	if (git_buf_len(file_content) < header_len + 1) {
		git_error_set(GIT_ERROR_REFERENCE, "corrupted loose reference file");
		return NULL;
	}

	/*
	 * Assume we have already checked for the header
	 * before calling this function
	 */
	refname_start += header_len;

	return refname_start;
}