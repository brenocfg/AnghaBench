#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  t; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ ge25519_p3 ;
struct TYPE_6__ {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ ge25519_aff ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_ec2d ; 

__attribute__((used)) static void ge25519_mixadd2(ge25519_p3 *r, const ge25519_aff *q)
{
  fe25519 a,b,t1,t2,c,d,e,f,g,h,qt;
  fe25519_mul(&qt, &q->x, &q->y);
  fe25519_sub(&a, &r->y, &r->x); /* A = (Y1-X1)*(Y2-X2) */
  fe25519_add(&b, &r->y, &r->x); /* B = (Y1+X1)*(Y2+X2) */
  fe25519_sub(&t1, &q->y, &q->x);
  fe25519_add(&t2, &q->y, &q->x);
  fe25519_mul(&a, &a, &t1);
  fe25519_mul(&b, &b, &t2);
  fe25519_sub(&e, &b, &a); /* E = B-A */
  fe25519_add(&h, &b, &a); /* H = B+A */
  fe25519_mul(&c, &r->t, &qt); /* C = T1*k*T2 */
  fe25519_mul(&c, &c, &ge25519_ec2d);
  fe25519_add(&d, &r->z, &r->z); /* D = Z1*2 */
  fe25519_sub(&f, &d, &c); /* F = D-C */
  fe25519_add(&g, &d, &c); /* G = D+C */
  fe25519_mul(&r->x, &e, &f);
  fe25519_mul(&r->y, &h, &g);
  fe25519_mul(&r->z, &g, &f);
  fe25519_mul(&r->t, &e, &h);
}