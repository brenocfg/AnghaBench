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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int git_buf_puts (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ git_buf_rfind (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_truncate (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int submodule_config_key_trunc_puts(git_buf *key, const char *suffix)
{
	ssize_t idx = git_buf_rfind(key, '.');
	git_buf_truncate(key, (size_t)(idx + 1));
	return git_buf_puts(key, suffix);
}