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
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ ge25519_p3 ;
typedef  int /*<<< orphan*/  fe25519 ;

/* Variables and functions */
 int fe25519_getparity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_invert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fe25519_pack (unsigned char*,int /*<<< orphan*/ *) ; 

void ge25519_pack(unsigned char r[32], const ge25519_p3 *p)
{
  fe25519 tx, ty, zi;
  fe25519_invert(&zi, &p->z); 
  fe25519_mul(&tx, &p->x, &zi);
  fe25519_mul(&ty, &p->y, &zi);
  fe25519_pack(r, &ty);
  r[31] ^= fe25519_getparity(&tx) << 7;
}