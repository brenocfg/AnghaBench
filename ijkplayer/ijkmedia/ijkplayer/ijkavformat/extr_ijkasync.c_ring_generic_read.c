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
struct TYPE_4__ {scalar_t__ read_pos; scalar_t__ read_back_capacity; int /*<<< orphan*/  fifo; } ;
typedef  TYPE_1__ RingBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  av_fifo_drain (int /*<<< orphan*/ ,scalar_t__) ; 
 int av_fifo_generic_peek_at (int /*<<< orphan*/ ,void*,scalar_t__,int,void (*) (void*,void*,int)) ; 
 int ring_size (TYPE_1__*) ; 

__attribute__((used)) static int ring_generic_read(RingBuffer *ring, void *dest, int buf_size, void (*func)(void*, void*, int))
{
    int ret;

    av_assert2(buf_size <= ring_size(ring));
    ret = av_fifo_generic_peek_at(ring->fifo, dest, ring->read_pos, buf_size, func);
    ring->read_pos += buf_size;

    if (ring->read_pos > ring->read_back_capacity) {
        av_fifo_drain(ring->fifo, ring->read_pos - ring->read_back_capacity);
        ring->read_pos = ring->read_back_capacity;
    }

    return ret;
}