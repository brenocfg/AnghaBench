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
struct TYPE_3__ {char* ptr; scalar_t__ asize; scalar_t__ size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 char* git_buf__initbuf ; 

void git_buf_clear(git_buf *buf)
{
	buf->size = 0;

	if (!buf->ptr) {
		buf->ptr = git_buf__initbuf;
		buf->asize = 0;
	}

	if (buf->asize > 0)
		buf->ptr[0] = '\0';
}