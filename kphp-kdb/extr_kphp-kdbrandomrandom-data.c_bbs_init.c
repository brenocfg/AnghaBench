#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bits; int ctx; int mlen; int tmp; scalar_t__ i; int /*<<< orphan*/ * m; int /*<<< orphan*/ * x; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ bbs_t ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_CTX_new () ; 
 int /*<<< orphan*/  BN_RECP_CTX_new () ; 
 int BN_RECP_CTX_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * BN_generate_prime (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* BN_new () ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_rshift1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_value_one () ; 
 int /*<<< orphan*/  assert (int) ; 
 int calloc (int,int) ; 
 int /*<<< orphan*/  prng_seed (char const* const,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int bbs_init (bbs_t *self, int bits, const char *const password_filename, int password_length) {
  if (bits < 256) {
    return -1;
  }
  self->bits = bits;
  self->ctx = BN_CTX_new ();
  assert (self->ctx);
  BIGNUM *three = BN_new ();
  assert (three);
  assert (1 == BN_set_word (three, 3));
  BIGNUM *four = BN_new ();
  assert (four);
  assert (1 == BN_set_word (four, 4));

  prng_seed (password_filename, password_length);
  vkprintf (2, "PRNG initialized.\n");
  self->bits = bits;
  vkprintf (2, "p was generated.\n");
  BIGNUM *t = BN_new (), *p = NULL, *q = NULL;
  while (1) {
    BIGNUM *p1 = BN_new (), *q1 = BN_new ();
    assert (p1 && q1);
    p = BN_generate_prime (NULL, bits / 2, 0, four, three, NULL, NULL);
    assert (p);
    BN_sub (p1, p, BN_value_one ());
    q = BN_generate_prime (NULL, bits / 2, 0, four, three, NULL, NULL);
    assert (q);
    BN_sub (q1, q, BN_value_one ());

    BN_rshift1 (p1, p1);
    BN_rshift1 (q1, q1);
    BN_gcd (t, p1, q1, self->ctx);
    BN_free (p1);
    BN_free (q1);

    if (BN_is_one (t)) {
      break;
    }
    vkprintf (2, "gcd ((p-1)/2, (q-1)/2) isn't 1.\n");
    BN_free (p);
    p = NULL;
    BN_free (q);
    q = NULL;
  }

  BN_free (three);
  BN_free (four);

  self->m = BN_new ();
  BN_mul (self->m, p, q, self->ctx);
  BN_clear_free (p);
  BN_clear_free (q);
  self->r = BN_RECP_CTX_new ();
  assert (1 == BN_RECP_CTX_set (self->r, self->m, self->ctx));

  self->mlen = BN_num_bytes (self->m);
  self->tmp = calloc ((self->mlen + 3) & -4, 1);
  assert (self->tmp);
  self->x = BN_new ();
  BN_set_word (self->x, 239);
  BN_gcd (t, self->x, self->m, self->ctx);
  assert (BN_is_one (t));
  BN_free (t);
  self->i = 0;

  return 0;
}