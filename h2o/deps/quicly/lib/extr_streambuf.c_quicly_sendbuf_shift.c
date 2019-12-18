#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_stream_t ;
struct TYPE_12__ {size_t len; TYPE_1__* cb; } ;
typedef  TYPE_3__ quicly_sendbuf_vec_t ;
struct TYPE_11__ {size_t size; scalar_t__ capacity; TYPE_3__* entries; } ;
struct TYPE_13__ {size_t off_in_first_vec; TYPE_2__ vecs; } ;
typedef  TYPE_4__ quicly_sendbuf_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* discard_vec ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  quicly_stream_sync_sendbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

void quicly_sendbuf_shift(quicly_stream_t *stream, quicly_sendbuf_t *sb, size_t delta)
{
    size_t i;

    for (i = 0; delta != 0; ++i) {
        assert(i < sb->vecs.size);
        quicly_sendbuf_vec_t *first_vec = sb->vecs.entries + i;
        size_t bytes_in_first_vec = first_vec->len - sb->off_in_first_vec;
        if (delta < bytes_in_first_vec) {
            sb->off_in_first_vec += delta;
            break;
        }
        delta -= bytes_in_first_vec;
        if (first_vec->cb->discard_vec != NULL)
            first_vec->cb->discard_vec(first_vec);
        sb->off_in_first_vec = 0;
    }
    if (i != 0) {
        if (sb->vecs.size != i) {
            memmove(sb->vecs.entries, sb->vecs.entries + i, (sb->vecs.size - i) * sizeof(*sb->vecs.entries));
            sb->vecs.size -= i;
        } else {
            free(sb->vecs.entries);
            sb->vecs.entries = NULL;
            sb->vecs.size = 0;
            sb->vecs.capacity = 0;
        }
    }
    quicly_stream_sync_sendbuf(stream, 0);
}