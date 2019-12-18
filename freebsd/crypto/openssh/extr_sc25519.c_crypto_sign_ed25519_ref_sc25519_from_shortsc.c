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
struct TYPE_5__ {scalar_t__* v; } ;
typedef  TYPE_1__ shortsc25519 ;
struct TYPE_6__ {scalar_t__* v; } ;
typedef  TYPE_2__ sc25519 ;

/* Variables and functions */

void sc25519_from_shortsc(sc25519 *r, const shortsc25519 *x)
{
  int i;
  for(i=0;i<16;i++)
    r->v[i] = x->v[i];
  for(i=0;i<16;i++)
    r->v[16+i] = 0;
}