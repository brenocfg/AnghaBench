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

/* Variables and functions */
 struct mbuf* SCTP_BUF_NEXT (struct mbuf*) ; 
 struct mbuf* sctp_add_pad_tombuf (struct mbuf*,int) ; 

struct mbuf *
sctp_pad_lastmbuf(struct mbuf *m, int padval, struct mbuf *last_mbuf)
{
	/* find the last mbuf in chain and pad it */
	struct mbuf *m_at;

	if (last_mbuf != NULL) {
		return (sctp_add_pad_tombuf(last_mbuf, padval));
	} else {
		for (m_at = m; m_at; m_at = SCTP_BUF_NEXT(m_at)) {
			if (SCTP_BUF_NEXT(m_at) == NULL) {
				return (sctp_add_pad_tombuf(m_at, padval));
			}
		}
	}
	return (NULL);
}