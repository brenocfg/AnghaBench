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
 scalar_t__ hash32_buf (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint32_t
hash_pkt(struct mbuf *m, uint32_t offset)
{
	uint32_t hash;

	hash = 0;

	while (m != NULL && offset > m->m_len) {
		/*
		 * The IP packet payload does not start in this mbuf, so
		 * need to figure out which mbuf it starts in and what offset
		 * into the mbuf's data region the payload starts at.
		 */
		offset -= m->m_len;
		m = m->m_next;
	}

	while (m != NULL) {
		/* Ensure there is data in the mbuf */
		if ((m->m_len - offset) > 0)
			hash = hash32_buf(m->m_data + offset,
			    m->m_len - offset, hash);

		m = m->m_next;
		offset = 0;
        }

	return (hash);
}