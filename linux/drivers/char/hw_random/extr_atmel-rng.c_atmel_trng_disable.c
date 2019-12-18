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
struct atmel_trng {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TRNG_CR ; 
 int /*<<< orphan*/  TRNG_KEY ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void atmel_trng_disable(struct atmel_trng *trng)
{
	writel(TRNG_KEY, trng->base + TRNG_CR);
}