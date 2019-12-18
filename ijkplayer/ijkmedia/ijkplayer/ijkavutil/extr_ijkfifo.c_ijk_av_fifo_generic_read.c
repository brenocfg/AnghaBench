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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {void* end; void* rptr; } ;
typedef  TYPE_1__ IjkFifoBuffer ;

/* Variables and functions */
 int FFMIN (void*,int) ; 
 int /*<<< orphan*/  ijk_av_fifo_drain (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

int ijk_av_fifo_generic_read(IjkFifoBuffer *f, void *dest, int buf_size,
                         void (*func)(void *, void *, int))
{
// Read memory barrier needed for SMP here in theory
    do {
        int len = FFMIN(f->end - f->rptr, buf_size);
        if (func)
            func(dest, f->rptr, len);
        else {
            memcpy(dest, f->rptr, len);
            dest = (uint8_t *)dest + len;
        }
// memory barrier needed for SMP here in theory
        ijk_av_fifo_drain(f, len);
        buf_size -= len;
    } while (buf_size > 0);
    return 0;
}