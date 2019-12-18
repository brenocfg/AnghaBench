#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* read_sequence; unsigned char* write_sequence; TYPE_1__* d; } ;
struct TYPE_8__ {TYPE_2__ rlayer; } ;
struct TYPE_6__ {unsigned char next_bitmap; int /*<<< orphan*/  w_epoch; int /*<<< orphan*/ * last_write_sequence; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  r_epoch; } ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int SSL3_CC_READ ; 
 int /*<<< orphan*/  dtls1_clear_received_buffer (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

void dtls1_reset_seq_numbers(SSL *s, int rw)
{
    unsigned char *seq;
    unsigned int seq_bytes = sizeof(s->rlayer.read_sequence);

    if (rw & SSL3_CC_READ) {
        seq = s->rlayer.read_sequence;
        s->rlayer.d->r_epoch++;
        memcpy(&s->rlayer.d->bitmap, &s->rlayer.d->next_bitmap,
               sizeof(s->rlayer.d->bitmap));
        memset(&s->rlayer.d->next_bitmap, 0, sizeof(s->rlayer.d->next_bitmap));

        /*
         * We must not use any buffered messages received from the previous
         * epoch
         */
        dtls1_clear_received_buffer(s);
    } else {
        seq = s->rlayer.write_sequence;
        memcpy(s->rlayer.d->last_write_sequence, seq,
               sizeof(s->rlayer.write_sequence));
        s->rlayer.d->w_epoch++;
    }

    memset(seq, 0, seq_bytes);
}