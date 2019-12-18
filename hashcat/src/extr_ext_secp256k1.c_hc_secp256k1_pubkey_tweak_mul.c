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
typedef  int u8 ;
typedef  int /*<<< orphan*/  secp256k1_scalar ;
typedef  int /*<<< orphan*/  secp256k1_pubkey ;
typedef  int /*<<< orphan*/  secp256k1_gej ;
struct TYPE_5__ {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;
typedef  TYPE_1__ secp256k1_ge ;
typedef  int /*<<< orphan*/  secp256k1_context ;

/* Variables and functions */
 int /*<<< orphan*/  SECP256K1_CONTEXT_NONE ; 
 int /*<<< orphan*/  SECP256K1_CONTEXT_VERIFY ; 
 int /*<<< orphan*/  SECP256K1_EC_COMPRESSED ; 
 int /*<<< orphan*/ * secp256k1_context_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secp256k1_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ec_pubkey_serialize (int /*<<< orphan*/ *,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ secp256k1_ec_pubkey_tweak_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  secp256k1_ecmult_const (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  secp256k1_fe_get_b32 (int*,int /*<<< orphan*/ *) ; 
 int secp256k1_fe_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_fe_normalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_ge_set_gej (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_pubkey_load (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ secp256k1_scalar_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secp256k1_scalar_set_b32 (int /*<<< orphan*/ *,int*,int*) ; 

bool hc_secp256k1_pubkey_tweak_mul (secp256k1_pubkey *pubkey, u8 *buf, size_t length)
{
  #if !defined (WITH_LIBSECP256K1)

  secp256k1_context *sctx = secp256k1_context_create (SECP256K1_CONTEXT_NONE);

  secp256k1_gej res;
  secp256k1_ge  pt;

  // load the public key and 32 byte scalar:

  secp256k1_pubkey_load (sctx, &pt, pubkey);

  int overflow = 0;

  secp256k1_scalar s;

  secp256k1_scalar_set_b32 (&s, buf, &overflow);

  if (overflow != 0)
  {
    secp256k1_scalar_clear (&s);

    secp256k1_context_destroy (sctx);

    return false;
  }

  if (secp256k1_scalar_is_zero (&s))
  {
    secp256k1_scalar_clear (&s);

    secp256k1_context_destroy (sctx);

    return false;
  }


  // main multiply operation:

  const size_t scalar_size = (length - 1) * 8;

  secp256k1_ecmult_const (&res, &pt, &s, scalar_size);
  secp256k1_ge_set_gej   (&pt, &res);
  secp256k1_fe_normalize (&pt.x);
  secp256k1_fe_normalize (&pt.y);


  // output:

  buf[0] = 0x02 | secp256k1_fe_is_odd (&pt.y);

  secp256k1_fe_get_b32 (buf + 1, &pt.x);


  // cleanup:

  secp256k1_scalar_clear (&s);

  secp256k1_context_destroy (sctx);

  #else

  // ATTENTION: this way to multiply was much slower in our tests

  secp256k1_context *sctx = secp256k1_context_create (SECP256K1_CONTEXT_VERIFY);


  // main multiply operation:

  if (secp256k1_ec_pubkey_tweak_mul (sctx, pubkey, buf) == 0)
  {
    secp256k1_context_destroy (sctx);

    return false;
  }


  // output:

  secp256k1_ec_pubkey_serialize (sctx, buf, &length, pubkey, SECP256K1_EC_COMPRESSED);


  // cleanup:

  secp256k1_context_destroy (sctx);

  #endif

  return true;
}