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
struct proc_data {size_t size; size_t capacity; char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 
 char* realloc (char*,size_t) ; 

void proc_buf_write(struct proc_data *buf, const void *data, size_t size) {
    if (buf->size + size > buf->capacity) {
        size_t new_capacity = buf->capacity;
        while (buf->size + size > new_capacity)
            new_capacity *= 2;
        char *new_data = realloc(buf->data, new_capacity);
        if (new_data == NULL) {
            // just give up, error reporting is a pain
            return;
        }
        buf->data = new_data;
        buf->capacity = new_capacity;
    }
    assert(buf->size + size <= buf->capacity);
    memcpy(&buf->data[buf->size], data, size);
    buf->size += size;
}