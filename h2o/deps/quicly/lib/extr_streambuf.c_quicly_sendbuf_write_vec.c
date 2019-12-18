#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_stream_t ;
struct TYPE_9__ {scalar_t__ len; } ;
typedef  TYPE_2__ quicly_sendbuf_vec_t ;
struct TYPE_8__ {int size; int capacity; TYPE_2__* entries; } ;
struct TYPE_10__ {int /*<<< orphan*/  bytes_written; TYPE_1__ vecs; } ;
typedef  TYPE_3__ quicly_sendbuf_t ;

/* Variables and functions */
 int PTLS_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  assert (int) ; 
 int quicly_stream_sync_sendbuf (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* realloc (TYPE_2__*,size_t) ; 

int quicly_sendbuf_write_vec(quicly_stream_t *stream, quicly_sendbuf_t *sb, quicly_sendbuf_vec_t *vec)
{
    assert(sb->vecs.size <= sb->vecs.capacity);

    if (sb->vecs.size == sb->vecs.capacity) {
        quicly_sendbuf_vec_t *new_entries;
        size_t new_capacity = sb->vecs.capacity == 0 ? 4 : sb->vecs.capacity * 2;
        if ((new_entries = realloc(sb->vecs.entries, new_capacity * sizeof(*sb->vecs.entries))) == NULL)
            return PTLS_ERROR_NO_MEMORY;
        sb->vecs.entries = new_entries;
        sb->vecs.capacity = new_capacity;
    }
    sb->vecs.entries[sb->vecs.size++] = *vec;
    sb->bytes_written += vec->len;

    return quicly_stream_sync_sendbuf(stream, 1);
}