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
 int /*<<< orphan*/  GIT_ZSTREAM_DEFLATE ; 
 int zstream_buf (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ) ; 

int git_zstream_deflatebuf(git_buf *out, const void *in, size_t in_len)
{
	return zstream_buf(out, in, in_len, GIT_ZSTREAM_DEFLATE);
}