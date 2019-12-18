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
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  write_lebn (unsigned char**,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void write_dsa(unsigned char **out, DSA *dsa, int ispub)
{
    int nbyte;
    const BIGNUM *p = NULL, *q = NULL, *g = NULL;
    const BIGNUM *pub_key = NULL, *priv_key = NULL;

    DSA_get0_pqg(dsa, &p, &q, &g);
    DSA_get0_key(dsa, &pub_key, &priv_key);
    nbyte = BN_num_bytes(p);
    write_lebn(out, p, nbyte);
    write_lebn(out, q, 20);
    write_lebn(out, g, nbyte);
    if (ispub)
        write_lebn(out, pub_key, nbyte);
    else
        write_lebn(out, priv_key, 20);
    /* Set "invalid" for seed structure values */
    memset(*out, 0xff, 24);
    *out += 24;
    return;
}