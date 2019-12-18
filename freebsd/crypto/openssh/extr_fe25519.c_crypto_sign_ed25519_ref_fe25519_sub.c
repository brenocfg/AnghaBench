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
struct TYPE_6__ {scalar_t__* v; } ;
typedef  TYPE_1__ fe25519 ;
typedef  scalar_t__ crypto_uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  reduce_add_sub (TYPE_1__*) ; 

void fe25519_sub(fe25519 *r, const fe25519 *x, const fe25519 *y)
{
  int i;
  crypto_uint32 t[32];
  t[0] = x->v[0] + 0x1da;
  t[31] = x->v[31] + 0xfe;
  for(i=1;i<31;i++) t[i] = x->v[i] + 0x1fe;
  for(i=0;i<32;i++) r->v[i] = t[i] - y->v[i];
  reduce_add_sub(r);
}