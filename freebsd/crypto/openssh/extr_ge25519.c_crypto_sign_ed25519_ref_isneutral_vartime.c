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
struct TYPE_3__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ ge25519_p3 ;

/* Variables and functions */
 int /*<<< orphan*/  fe25519_iseq_vartime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_iszero (int /*<<< orphan*/ *) ; 

int ge25519_isneutral_vartime(const ge25519_p3 *p)
{
  int ret = 1;
  if(!fe25519_iszero(&p->x)) ret = 0;
  if(!fe25519_iseq_vartime(&p->y, &p->z)) ret = 0;
  return ret;
}