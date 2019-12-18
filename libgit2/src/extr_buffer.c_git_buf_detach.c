#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* ptr; scalar_t__ asize; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 char* git_buf__oom ; 
 int /*<<< orphan*/  git_buf_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

char *git_buf_detach(git_buf *buf)
{
	char *data = buf->ptr;

	if (buf->asize == 0 || buf->ptr == git_buf__oom)
		return NULL;

	git_buf_init(buf, 0);

	return data;
}