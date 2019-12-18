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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ base; scalar_t__ off; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 int ptls_buffer_reserve (TYPE_1__*,size_t) ; 
 scalar_t__ quicly_encodev (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t quicly_encodev_capacity (int /*<<< orphan*/ ) ; 

int quicly_tls_push_varint(ptls_buffer_t *buf, uint64_t v)
{
    size_t capacity = quicly_encodev_capacity(v);
    int ret;

    if ((ret = ptls_buffer_reserve(buf, capacity)) != 0)
        return ret;
    buf->off = quicly_encodev(buf->base + buf->off, v) - buf->base;

    return 0;
}