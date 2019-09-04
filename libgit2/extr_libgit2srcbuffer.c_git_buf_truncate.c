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
struct TYPE_3__ {size_t size; size_t asize; char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */

void git_buf_truncate(git_buf *buf, size_t len)
{
	if (len >= buf->size)
		return;

	buf->size = len;
	if (buf->size < buf->asize)
		buf->ptr[buf->size] = '\0';
}