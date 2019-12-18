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
struct TYPE_3__ {int size; char* ptr; int asize; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git__isspace (char) ; 

void git_buf_rtrim(git_buf *buf)
{
	while (buf->size > 0) {
		if (!git__isspace(buf->ptr[buf->size - 1]))
			break;

		buf->size--;
	}

	if (buf->asize > buf->size)
		buf->ptr[buf->size] = '\0';
}