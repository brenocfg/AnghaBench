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
typedef  int /*<<< orphan*/  sc25519 ;
typedef  int /*<<< orphan*/  ge25519 ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_hash_sha512 (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ge25519_pack (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_scalarmult_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  randombytes (unsigned char*,int) ; 
 int /*<<< orphan*/  sc25519_from32bytes (int /*<<< orphan*/ *,unsigned char*) ; 

int crypto_sign_ed25519_keypair(
    unsigned char *pk,
    unsigned char *sk
    )
{
  sc25519 scsk;
  ge25519 gepk;
  unsigned char extsk[64];
  int i;

  randombytes(sk, 32);
  crypto_hash_sha512(extsk, sk, 32);
  extsk[0] &= 248;
  extsk[31] &= 127;
  extsk[31] |= 64;

  sc25519_from32bytes(&scsk,extsk);
  
  ge25519_scalarmult_base(&gepk, &scsk);
  ge25519_pack(pk, &gepk);
  for(i=0;i<32;i++)
    sk[32 + i] = pk[i];
  return 0;
}