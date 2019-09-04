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
struct TYPE_4__ {int leftover; unsigned char* buffer; } ;
typedef  TYPE_1__ poly1305_state_internal_t ;

/* Variables and functions */
 unsigned long long poly1305_block_size ; 
 int /*<<< orphan*/  poly1305_blocks (TYPE_1__*,unsigned char const*,unsigned long long) ; 

__attribute__((used)) static void
poly1305_update(poly1305_state_internal_t *st, const unsigned char *m,
                unsigned long long bytes)
{
    unsigned long long i;

    /* handle leftover */
    if (st->leftover) {
        unsigned long long want = (poly1305_block_size - st->leftover);

        if (want > bytes) {
            want = bytes;
        }
        for (i = 0; i < want; i++) {
            st->buffer[st->leftover + i] = m[i];
        }
        bytes -= want;
        m += want;
        st->leftover += want;
        if (st->leftover < poly1305_block_size) {
            return;
        }
        poly1305_blocks(st, st->buffer, poly1305_block_size);
        st->leftover = 0;
    }

    /* process full blocks */
    if (bytes >= poly1305_block_size) {
        unsigned long long want = (bytes & ~(poly1305_block_size - 1));

        poly1305_blocks(st, m, want);
        m += want;
        bytes -= want;
    }

    /* store leftover */
    if (bytes) {
        for (i = 0; i < bytes; i++) {
            st->buffer[st->leftover + i] = m[i];
        }
        st->leftover += bytes;
    }
}