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
typedef  scalar_t__ uint32_t ;
struct mbuf {scalar_t__ m_len; scalar_t__ m_data; struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calculate_crc32c (scalar_t__,unsigned char*,unsigned int) ; 
 scalar_t__ sctp_finalize_crc32c (scalar_t__) ; 

uint32_t
sctp_calculate_cksum(struct mbuf *m, uint32_t offset)
{
	uint32_t base = 0xffffffff;

	while (offset > 0) {
		KASSERT(m != NULL, ("sctp_calculate_cksum, offset > length of mbuf chain"));
		if (offset < (uint32_t)m->m_len) {
			break;
		}
		offset -= m->m_len;
		m = m->m_next;
	}
	if (offset > 0) {
		base = calculate_crc32c(base,
		    (unsigned char *)(m->m_data + offset),
		    (unsigned int)(m->m_len - offset));
		m = m->m_next;
	}
	while (m != NULL) {
		base = calculate_crc32c(base,
		    (unsigned char *)m->m_data,
		    (unsigned int)m->m_len);
		m = m->m_next;
	}
	base = sctp_finalize_crc32c(base);
	return (base);
}