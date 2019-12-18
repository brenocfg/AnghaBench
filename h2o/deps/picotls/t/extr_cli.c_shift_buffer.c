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
struct TYPE_3__ {size_t off; scalar_t__ base; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 

__attribute__((used)) static void shift_buffer(ptls_buffer_t *buf, size_t delta)
{
    if (delta != 0) {
        assert(delta <= buf->off);
        if (delta != buf->off)
            memmove(buf->base, buf->base + delta, buf->off - delta);
        buf->off -= delta;
    }
}