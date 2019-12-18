#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  shortsc25519 ;
typedef  int /*<<< orphan*/  sc25519 ;

/* Variables and functions */
 int /*<<< orphan*/  sc25519_from_shortsc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sc25519_mul (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

void sc25519_mul_shortsc(sc25519 *r, const sc25519 *x, const shortsc25519 *y)
{
  sc25519 t;
  sc25519_from_shortsc(&t, y);
  sc25519_mul(r, x, &t);
}