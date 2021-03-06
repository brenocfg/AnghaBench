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
struct TYPE_4__ {scalar_t__ rptr; scalar_t__ end; scalar_t__ buffer; int rndx; } ;
typedef  TYPE_1__ IjkFifoBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ijk_av_fifo_size (TYPE_1__*) ; 

void ijk_av_fifo_drain(IjkFifoBuffer *f, int size)
{
    assert(ijk_av_fifo_size(f) >= size);
    f->rptr += size;
    if (f->rptr >= f->end)
        f->rptr -= f->end - f->buffer;
    f->rndx += size;
}