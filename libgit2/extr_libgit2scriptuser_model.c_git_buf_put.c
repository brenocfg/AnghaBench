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
struct TYPE_3__ {size_t size; scalar_t__* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__* __coverity_alloc__ (size_t) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,char const*,size_t) ; 

int git_buf_put(git_buf *buf, const char *data, size_t len)
{
    buf->ptr = __coverity_alloc__(buf->size + len + 1);
    memmove(buf->ptr + buf->size, data, len);
    buf->size += len;
    buf->ptr[buf->size + len] = 0;
    return 0;
}