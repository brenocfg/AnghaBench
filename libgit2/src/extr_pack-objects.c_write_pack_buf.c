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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int git_buf_put (int /*<<< orphan*/ *,void*,size_t) ; 

__attribute__((used)) static int write_pack_buf(void *buf, size_t size, void *data)
{
	git_buf *b = (git_buf *)data;
	return git_buf_put(b, buf, size);
}