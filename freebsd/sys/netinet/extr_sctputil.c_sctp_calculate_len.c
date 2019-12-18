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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ SCTP_BUF_LEN (struct mbuf*) ; 
 struct mbuf* SCTP_BUF_NEXT (struct mbuf*) ; 

uint32_t
sctp_calculate_len(struct mbuf *m)
{
	uint32_t tlen = 0;
	struct mbuf *at;

	at = m;
	while (at) {
		tlen += SCTP_BUF_LEN(at);
		at = SCTP_BUF_NEXT(at);
	}
	return (tlen);
}