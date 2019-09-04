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
 scalar_t__ git_buf_rfind_next (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  git_buf_truncate (int /*<<< orphan*/ *,size_t) ; 

void git_buf_rtruncate_at_char(git_buf *buf, char separator)
{
	ssize_t idx = git_buf_rfind_next(buf, separator);
	git_buf_truncate(buf, idx < 0 ? 0 : (size_t)idx);
}