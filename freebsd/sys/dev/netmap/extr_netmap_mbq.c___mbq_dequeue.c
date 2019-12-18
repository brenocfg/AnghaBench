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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct mbq {int /*<<< orphan*/  count; int /*<<< orphan*/ * tail; struct mbuf* head; } ;

/* Variables and functions */

__attribute__((used)) static inline struct mbuf *__mbq_dequeue(struct mbq *q)
{
    struct mbuf *ret = NULL;

    if (q->head) {
        ret = q->head;
        q->head = ret->m_nextpkt;
        if (q->head == NULL) {
            q->tail = NULL;
        }
        q->count--;
        ret->m_nextpkt = NULL;
    }

    return ret;
}