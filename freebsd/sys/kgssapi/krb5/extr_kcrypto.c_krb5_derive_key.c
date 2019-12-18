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
struct mbuf {int m_len; int /*<<< orphan*/ * m_data; } ;
struct krb5_key_state {struct krb5_encryption_class* ks_class; } ;
struct krb5_encryption_class {int ec_blocklen; int ec_keybits; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_GSSAPI ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct krb5_key_state* krb5_create_key (struct krb5_encryption_class const*) ; 
 int /*<<< orphan*/  krb5_encrypt (struct krb5_key_state*,struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_n_fold (int /*<<< orphan*/ *,int,void*,size_t) ; 
 int /*<<< orphan*/  krb5_random_to_key (struct krb5_key_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup (int,int) ; 

struct krb5_key_state *
krb5_derive_key(struct krb5_key_state *inkey,
    void *constant, size_t constantlen)
{
	struct krb5_key_state *dk;
	const struct krb5_encryption_class *ec = inkey->ks_class;
	uint8_t *folded;
	uint8_t *bytes, *p, *q;
	struct mbuf *m;
	int randomlen, i;

	/*
	 * Expand the constant to blocklen bytes.
	 */
	folded = malloc(ec->ec_blocklen, M_GSSAPI, M_WAITOK);
	krb5_n_fold(folded, ec->ec_blocklen, constant, constantlen);

	/*
	 * Generate enough bytes for keybits rounded up to a multiple
	 * of blocklen.
	 */
	randomlen = roundup(ec->ec_keybits / 8, ec->ec_blocklen);
	bytes = malloc(randomlen, M_GSSAPI, M_WAITOK);
	MGET(m, M_WAITOK, MT_DATA);
	m->m_len = ec->ec_blocklen;
	for (i = 0, p = bytes, q = folded; i < randomlen;
	     q = p, i += ec->ec_blocklen, p += ec->ec_blocklen) {
		bcopy(q, m->m_data, ec->ec_blocklen);
		krb5_encrypt(inkey, m, 0, ec->ec_blocklen, NULL, 0);
		bcopy(m->m_data, p, ec->ec_blocklen);
	}
	m_free(m);

	dk = krb5_create_key(ec);
	krb5_random_to_key(dk, bytes);

	free(folded, M_GSSAPI);
	free(bytes, M_GSSAPI);

	return (dk);
}