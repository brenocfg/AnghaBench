#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pqueue ;
typedef  int /*<<< orphan*/  piterator ;
struct TYPE_11__ {scalar_t__ data; } ;
typedef  TYPE_3__ pitem ;
struct TYPE_9__ {int /*<<< orphan*/  is_ccs; int /*<<< orphan*/  seq; } ;
struct TYPE_12__ {TYPE_1__ msg_header; } ;
typedef  TYPE_4__ hm_fragment ;
struct TYPE_13__ {TYPE_2__* d1; } ;
struct TYPE_10__ {int /*<<< orphan*/ * sent_messages; } ;
typedef  TYPE_5__ SSL ;

/* Variables and functions */
 scalar_t__ dtls1_get_queue_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dtls1_retransmit_message (TYPE_5__*,unsigned short,int*) ; 
 int /*<<< orphan*/  pqueue_iterator (int /*<<< orphan*/ *) ; 
 TYPE_3__* pqueue_next (int /*<<< orphan*/ *) ; 

int dtls1_retransmit_buffered_messages(SSL *s)
{
    pqueue *sent = s->d1->sent_messages;
    piterator iter;
    pitem *item;
    hm_fragment *frag;
    int found = 0;

    iter = pqueue_iterator(sent);

    for (item = pqueue_next(&iter); item != NULL; item = pqueue_next(&iter)) {
        frag = (hm_fragment *)item->data;
        if (dtls1_retransmit_message(s, (unsigned short)
                                     dtls1_get_queue_priority
                                     (frag->msg_header.seq,
                                      frag->msg_header.is_ccs), &found) <= 0)
            return -1;
    }

    return 1;
}