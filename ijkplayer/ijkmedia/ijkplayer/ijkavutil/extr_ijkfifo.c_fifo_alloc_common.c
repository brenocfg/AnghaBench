#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* buffer; void* end; } ;
typedef  TYPE_1__ IjkFifoBuffer ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  ijk_av_fifo_reset (TYPE_1__*) ; 

__attribute__((used)) static IjkFifoBuffer *fifo_alloc_common(void *buffer, size_t size)
{
    IjkFifoBuffer *f;
    if (!buffer)
        return NULL;
    f = calloc(1, sizeof(IjkFifoBuffer));
    if (!f) {
        free(buffer);
        return NULL;
    }
    f->buffer = buffer;
    f->end    = f->buffer + size;
    ijk_av_fifo_reset(f);
    return f;
}