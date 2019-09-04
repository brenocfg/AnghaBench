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
struct TYPE_3__ {size_t size; scalar_t__ asize; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ ,size_t) ; 

void git_buf_copy_cstr(char *data, size_t datasize, const git_buf *buf)
{
	size_t copylen;

	assert(data && datasize && buf);

	data[0] = '\0';

	if (buf->size == 0 || buf->asize <= 0)
		return;

	copylen = buf->size;
	if (copylen > datasize - 1)
		copylen = datasize - 1;
	memmove(data, buf->ptr, copylen);
	data[copylen] = '\0';
}