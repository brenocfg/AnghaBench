#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ ge25519_aff ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  cmov_aff (TYPE_1__*,TYPE_1__*,int) ; 
 int equal (char,int) ; 
 int /*<<< orphan*/  fe25519_cmov (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe25519_neg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ge25519_base_multiples_affine ; 
 int /*<<< orphan*/  negative (char) ; 

__attribute__((used)) static void choose_t(ge25519_aff *t, unsigned long long pos, signed char b)
{
  /* constant time */
  fe25519 v;
  *t = ge25519_base_multiples_affine[5*pos+0];
  cmov_aff(t, &ge25519_base_multiples_affine[5*pos+1],equal(b,1) | equal(b,-1));
  cmov_aff(t, &ge25519_base_multiples_affine[5*pos+2],equal(b,2) | equal(b,-2));
  cmov_aff(t, &ge25519_base_multiples_affine[5*pos+3],equal(b,3) | equal(b,-3));
  cmov_aff(t, &ge25519_base_multiples_affine[5*pos+4],equal(b,-4));
  fe25519_neg(&v, &t->x);
  fe25519_cmov(&t->x, &v, negative(b));
}