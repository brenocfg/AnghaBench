#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; int /*<<< orphan*/ * g; int /*<<< orphan*/ * q; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bn2bin (int /*<<< orphan*/  const*,...) ; 
 unsigned char* BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_get0_key (TYPE_1__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DSA_get0_pqg (TYPE_1__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool
ldns_key_dsa2bin(unsigned char *data, DSA *k, uint16_t *size)
{
	uint8_t T;
	const BIGNUM *p, *q, *g;
	const BIGNUM *pub_key, *priv_key;

	if (!k) {
		return false;
	}
	
	/* See RFC2536 */
# ifdef HAVE_DSA_GET0_PQG
	DSA_get0_pqg(k, &p, &q, &g);
# else
	p = k->p; q = k->q; g = k->g;
# endif
# ifdef HAVE_DSA_GET0_KEY
	DSA_get0_key(k, &pub_key, &priv_key);
# else
	pub_key = k->pub_key; priv_key = k->priv_key;
# endif
	(void)priv_key;
	*size = (uint16_t)BN_num_bytes(p);
	T = (*size - 64) / 8;

	if (T > 8) {
#ifdef STDERR_MSGS
		fprintf(stderr, "DSA key with T > 8 (ie. > 1024 bits)");
		fprintf(stderr, " not implemented\n");
#endif
		return false;
	}

	/* size = 64 + (T * 8); */
	memset(data, 0, 21 + *size * 3);
	data[0] = (unsigned char)T;
	BN_bn2bin(q, data + 1 ); 		/* 20 octects */
	BN_bn2bin(p, data + 21 ); 		/* offset octects */
	BN_bn2bin(g, data + 21 + *size * 2 - BN_num_bytes(g));
	BN_bn2bin(pub_key,data + 21 + *size * 3 - BN_num_bytes(pub_key));
	*size = 21 + *size * 3;
	return true;
}