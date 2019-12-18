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
struct TYPE_4__ {scalar_t__* v; } ;
typedef  TYPE_1__ sc25519 ;

/* Variables and functions */

int sc25519_lt_vartime(const sc25519 *x, const sc25519 *y)
{
  int i;
  for(i=31;i>=0;i--)
  {
    if(x->v[i] < y->v[i]) return 1;
    if(x->v[i] > y->v[i]) return 0;
  }
  return 0;
}