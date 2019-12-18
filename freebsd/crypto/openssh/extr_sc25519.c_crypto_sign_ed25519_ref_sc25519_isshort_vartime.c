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
struct TYPE_3__ {scalar_t__* v; } ;
typedef  TYPE_1__ sc25519 ;

/* Variables and functions */

int sc25519_isshort_vartime(const sc25519 *x)
{
  int i;
  for(i=31;i>15;i--)
    if(x->v[i] != 0) return 0;
  return 1;
}