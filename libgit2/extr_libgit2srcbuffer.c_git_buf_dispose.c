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
struct TYPE_4__ {scalar_t__ asize; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_buf__oom ; 
 int /*<<< orphan*/  git_buf_init (TYPE_1__*,int /*<<< orphan*/ ) ; 

void git_buf_dispose(git_buf *buf)
{
	if (!buf) return;

	if (buf->asize > 0 && buf->ptr != NULL && buf->ptr != git_buf__oom)
		git__free(buf->ptr);

	git_buf_init(buf, 0);
}