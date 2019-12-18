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
 char const* get_commit_output_encoding () ; 
 char const* git_log_output_encoding ; 

const char *get_log_output_encoding(void)
{
	return git_log_output_encoding ? git_log_output_encoding
		: get_commit_output_encoding();
}