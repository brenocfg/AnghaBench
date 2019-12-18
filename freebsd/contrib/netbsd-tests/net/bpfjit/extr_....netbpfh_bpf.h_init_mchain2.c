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
typedef  int /*<<< orphan*/  uint8_t ;
struct mbuf {char* m_data; size_t m_len; struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mbuf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline const uint8_t *
init_mchain2(struct mbuf *mb1, struct mbuf *mb2,
    unsigned char pkt[], size_t pktsize, size_t split)
{

	(void)memset(mb1, 0, sizeof(*mb1));
	mb1->m_data = (char *)pkt;
	mb1->m_next = (split < pktsize) ? mb2 : NULL;
	mb1->m_len = (split < pktsize) ? split : pktsize;

	if (split < pktsize) {
		(void)memset(mb2, 0, sizeof(*mb2));
		mb2->m_next = NULL;
		mb2->m_data = (char *)&pkt[split];
		mb2->m_len = pktsize - split;
	}

	return (const uint8_t*)mb1;
}