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
struct TYPE_3__ {int /*<<< orphan*/  i; int /*<<< orphan*/ * x; int /*<<< orphan*/  ctx; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ bbs_t ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int BN_get_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mask_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_mod_mul_reciprocal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  assert (int) ; 

int bbs_next_random_byte (bbs_t *self) {
  BIGNUM *z = BN_new ();
  BN_mod_mul_reciprocal (z, self->x, self->x, self->r, self->ctx);
  BN_mask_bits (self->x, 8);
  int r = BN_get_word (self->x);
  assert (r >= 0 && r < 256);
  BN_clear_free (self->x);
  self->x = z;
  ++(self->i);
  return r;
}