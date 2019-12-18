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
struct buffer {int size; int index; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,char*,size_t) ; 
 size_t min (size_t,int) ; 

__attribute__((used)) static size_t
buffer_read(struct buffer *buf, void *dataptr, size_t len)
{
    len = min(len, buf->size - buf->index);
    memcpy(dataptr, (char*)buf->data + buf->index, len);
    buf->index += len;
    return len;
}