#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  quicly_stream_t ;
struct TYPE_9__ {size_t len; TYPE_1__* cb; } ;
typedef  TYPE_3__ quicly_sendbuf_vec_t ;
struct TYPE_8__ {size_t size; TYPE_3__* entries; } ;
struct TYPE_10__ {TYPE_2__ vecs; scalar_t__ off_in_first_vec; } ;
typedef  TYPE_4__ quicly_sendbuf_t ;
struct TYPE_7__ {int (* flatten_vec ) (TYPE_3__*,void*,size_t,size_t) ;} ;

/* Variables and functions */
 int stub1 (TYPE_3__*,void*,size_t,size_t) ; 

int quicly_sendbuf_emit(quicly_stream_t *stream, quicly_sendbuf_t *sb, size_t off, void *dst, size_t *len, int *wrote_all)
{
    size_t vec_index, capacity = *len;
    int ret;

    off += sb->off_in_first_vec;
    for (vec_index = 0; capacity != 0 && vec_index < sb->vecs.size; ++vec_index) {
        quicly_sendbuf_vec_t *vec = sb->vecs.entries + vec_index;
        if (off < vec->len) {
            size_t bytes_flatten = vec->len - off;
            int partial = 0;
            if (capacity < bytes_flatten) {
                bytes_flatten = capacity;
                partial = 1;
            }
            if ((ret = vec->cb->flatten_vec(vec, dst, off, bytes_flatten)) != 0)
                return ret;
            dst = (uint8_t *)dst + bytes_flatten;
            capacity -= bytes_flatten;
            off = 0;
            if (partial)
                break;
        } else {
            off -= vec->len;
        }
    }

    if (capacity == 0 && vec_index < sb->vecs.size) {
        *wrote_all = 0;
    } else {
        *len = *len - capacity;
        *wrote_all = 1;
    }

    return 0;
}