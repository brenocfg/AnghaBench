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
struct TYPE_4__ {int /*<<< orphan*/  ptr; scalar_t__ size; scalar_t__ asize; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE_SIZE (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  git_buf__initbuf ; 

int git_buf_init(git_buf *buf, size_t initial_size)
{
	buf->asize = 0;
	buf->size = 0;
	buf->ptr = git_buf__initbuf;

	ENSURE_SIZE(buf, initial_size);

	return 0;
}