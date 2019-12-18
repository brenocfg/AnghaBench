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
struct replay_opts {int dummy; } ;

/* Variables and functions */
 char const* git_path_seq_dir () ; 
 scalar_t__ is_rebase_i (struct replay_opts const*) ; 
 char const* rebase_path () ; 

__attribute__((used)) static const char *get_dir(const struct replay_opts *opts)
{
	if (is_rebase_i(opts))
		return rebase_path();
	return git_path_seq_dir();
}