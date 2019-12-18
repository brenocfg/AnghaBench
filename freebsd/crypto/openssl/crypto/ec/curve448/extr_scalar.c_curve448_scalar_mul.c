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
typedef  int /*<<< orphan*/  const curve448_scalar_t ;

/* Variables and functions */
 int /*<<< orphan*/  sc_montmul (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const sc_r2 ; 

void curve448_scalar_mul(curve448_scalar_t out, const curve448_scalar_t a,
                         const curve448_scalar_t b)
{
    sc_montmul(out, a, b);
    sc_montmul(out, out, sc_r2);
}