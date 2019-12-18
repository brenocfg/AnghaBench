#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sc25519 ;
struct TYPE_4__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  t; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ ge25519_p3 ;
typedef  int /*<<< orphan*/  ge25519_aff ;

/* Variables and functions */
 int /*<<< orphan*/  choose_t (int /*<<< orphan*/ *,unsigned long long,char) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_setone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge25519_mixadd2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc25519_window3 (char*,int /*<<< orphan*/  const*) ; 

void ge25519_scalarmult_base(ge25519_p3 *r, const sc25519 *s)
{
  signed char b[85];
  int i;
  ge25519_aff t;
  sc25519_window3(b,s);

  choose_t((ge25519_aff *)r, 0, b[0]);
  fe25519_setone(&r->z);
  fe25519_mul(&r->t, &r->x, &r->y);
  for(i=1;i<85;i++)
  {
    choose_t(&t, (unsigned long long) i, b[i]);
    ge25519_mixadd2(r, &t);
  }
}