#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct q_pkt {int pt_qout; int pt_tx; scalar_t__ next; int /*<<< orphan*/  pktlen; } ;
struct _qs {int qt_qout; int qt_tx; int /*<<< orphan*/  tx; scalar_t__ prod_tail; int /*<<< orphan*/  cur_len; int /*<<< orphan*/  cur_caplen; int /*<<< orphan*/  cur_pkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND (char*,int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  nm_pkt_copy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pad (int /*<<< orphan*/ ) ; 
 struct q_pkt* pkt_at (struct _qs*,scalar_t__) ; 

__attribute__((used)) static inline int
enq(struct _qs *q)
{
    struct q_pkt *p = pkt_at(q, q->prod_tail);

    /* hopefully prefetch has been done ahead */
    nm_pkt_copy(q->cur_pkt, (char *)(p+1), q->cur_caplen);
    p->pktlen = q->cur_len;
    p->pt_qout = q->qt_qout;
    p->pt_tx = q->qt_tx;
    p->next = q->prod_tail + pad(q->cur_len) + sizeof(struct q_pkt);
    ND("enqueue len %d at %d new tail %ld qout %.6f tx %.6f",
        q->cur_len, (int)q->prod_tail, p->next,
        1e-9*p->pt_qout, 1e-9*p->pt_tx);
    q->prod_tail = p->next;
    q->tx++;
    return 0;
}