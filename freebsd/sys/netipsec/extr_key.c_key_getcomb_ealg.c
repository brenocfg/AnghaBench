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
typedef  int /*<<< orphan*/  u_long ;
struct sadb_comb {int sadb_comb_encrypt; int sadb_comb_encrypt_minbits; void* sadb_comb_encrypt_maxbits; } ;
struct mbuf {int m_len; struct mbuf* m_next; } ;
struct enc_xform {int /*<<< orphan*/  maxkey; int /*<<< orphan*/  minkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSEC_ASSERT (int,char*) ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int const MLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_ALIGN (struct mbuf*,int const) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PFKEY_ALIGN8 (int) ; 
 int SADB_EALG_MAX ; 
 scalar_t__ V_ipsec_esp_auth ; 
 void* V_ipsec_esp_keymin ; 
 void* _BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct sadb_comb*,int) ; 
 int /*<<< orphan*/  caddr_t ; 
 struct enc_xform* enc_algorithm_lookup (int) ; 
 struct mbuf* key_getcomb_ah () ; 
 int /*<<< orphan*/  key_getcomb_setlifetime (struct sadb_comb*) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_pulldown (struct mbuf*,int,int const,int*) ; 
 struct sadb_comb* mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
key_getcomb_ealg(void)
{
	struct sadb_comb *comb;
	const struct enc_xform *algo;
	struct mbuf *result = NULL, *m, *n;
	int encmin;
	int i, off, o;
	int totlen;
	const int l = PFKEY_ALIGN8(sizeof(struct sadb_comb));

	m = NULL;
	for (i = 1; i <= SADB_EALG_MAX; i++) {
		algo = enc_algorithm_lookup(i);
		if (algo == NULL)
			continue;

		/* discard algorithms with key size smaller than system min */
		if (_BITS(algo->maxkey) < V_ipsec_esp_keymin)
			continue;
		if (_BITS(algo->minkey) < V_ipsec_esp_keymin)
			encmin = V_ipsec_esp_keymin;
		else
			encmin = _BITS(algo->minkey);

		if (V_ipsec_esp_auth)
			m = key_getcomb_ah();
		else {
			IPSEC_ASSERT(l <= MLEN,
				("l=%u > MLEN=%lu", l, (u_long) MLEN));
			MGET(m, M_NOWAIT, MT_DATA);
			if (m) {
				M_ALIGN(m, l);
				m->m_len = l;
				m->m_next = NULL;
				bzero(mtod(m, caddr_t), m->m_len);
			}
		}
		if (!m)
			goto fail;

		totlen = 0;
		for (n = m; n; n = n->m_next)
			totlen += n->m_len;
		IPSEC_ASSERT((totlen % l) == 0, ("totlen=%u, l=%u", totlen, l));

		for (off = 0; off < totlen; off += l) {
			n = m_pulldown(m, off, l, &o);
			if (!n) {
				/* m is already freed */
				goto fail;
			}
			comb = (struct sadb_comb *)(mtod(n, caddr_t) + o);
			bzero(comb, sizeof(*comb));
			key_getcomb_setlifetime(comb);
			comb->sadb_comb_encrypt = i;
			comb->sadb_comb_encrypt_minbits = encmin;
			comb->sadb_comb_encrypt_maxbits = _BITS(algo->maxkey);
		}

		if (!result)
			result = m;
		else
			m_cat(result, m);
	}

	return result;

 fail:
	if (result)
		m_freem(result);
	return NULL;
}