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
struct TYPE_3__ {unsigned char* v; } ;
typedef  TYPE_1__ sc25519 ;

/* Variables and functions */

void sc25519_to32bytes(unsigned char r[32], const sc25519 *x)
{
  int i;
  for(i=0;i<32;i++) r[i] = x->v[i];
}