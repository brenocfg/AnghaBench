#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned char* read_sequence; } ;
struct TYPE_7__ {unsigned long map; int /*<<< orphan*/  max_seq_num; } ;
struct TYPE_6__ {TYPE_5__ rlayer; } ;
typedef  TYPE_1__ SSL ;
typedef  TYPE_2__ DTLS1_BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  RECORD_LAYER_get_rrec (TYPE_5__*) ; 
 int /*<<< orphan*/  SSL3_RECORD_set_seq_num (int /*<<< orphan*/ ,unsigned char const*) ; 
 int satsub64be (unsigned char const*,int /*<<< orphan*/ ) ; 

int dtls1_record_replay_check(SSL *s, DTLS1_BITMAP *bitmap)
{
    int cmp;
    unsigned int shift;
    const unsigned char *seq = s->rlayer.read_sequence;

    cmp = satsub64be(seq, bitmap->max_seq_num);
    if (cmp > 0) {
        SSL3_RECORD_set_seq_num(RECORD_LAYER_get_rrec(&s->rlayer), seq);
        return 1;               /* this record in new */
    }
    shift = -cmp;
    if (shift >= sizeof(bitmap->map) * 8)
        return 0;               /* stale, outside the window */
    else if (bitmap->map & (1UL << shift))
        return 0;               /* record previously received */

    SSL3_RECORD_set_seq_num(RECORD_LAYER_get_rrec(&s->rlayer), seq);
    return 1;
}