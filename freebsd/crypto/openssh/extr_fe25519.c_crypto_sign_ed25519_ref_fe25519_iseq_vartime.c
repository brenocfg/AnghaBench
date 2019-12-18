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
struct TYPE_5__ {scalar_t__* v; } ;
typedef  TYPE_1__ fe25519 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_freeze (TYPE_1__*) ; 

int fe25519_iseq_vartime(const fe25519 *x, const fe25519 *y)
{
  int i;
  fe25519 t1 = *x;
  fe25519 t2 = *y;
  fe25519_freeze(&t1);
  fe25519_freeze(&t2);
  for(i=0;i<32;i++)
    if(t1.v[i] != t2.v[i]) return 0;
  return 1;
}