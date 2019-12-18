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
struct mbuf {int dummy; } ;
struct mbq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* mbq_dequeue (struct mbq*) ; 
 struct mbuf* mbq_safe_dequeue (struct mbq*) ; 

__attribute__((used)) static void __mbq_purge(struct mbq *q, int safe)
{
    struct mbuf *m;

    for (;;) {
        m = safe ? mbq_safe_dequeue(q) : mbq_dequeue(q);
        if (m) {
            m_freem(m);
        } else {
            break;
        }
    }
}