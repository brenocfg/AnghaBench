#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ptr; size_t size; scalar_t__ asize; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_is_allocated (TYPE_1__*) ; 

void git_buf_attach_notowned(git_buf *buf, const char *ptr, size_t size)
{
	if (git_buf_is_allocated(buf))
		git_buf_dispose(buf);

	if (!size) {
		git_buf_init(buf, 0);
	} else {
		buf->ptr = (char *)ptr;
		buf->asize = 0;
		buf->size = size;
	}
}