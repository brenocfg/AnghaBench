#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ is_git_directory (char const*) ; 
 char const* read_gitfile_gently (char const*,int*) ; 

const char *resolve_gitdir_gently(const char *suspect, int *return_error_code)
{
	if (is_git_directory(suspect))
		return suspect;
	return read_gitfile_gently(suspect, return_error_code);
}