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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_add (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpacf_trng (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  trng_hwrng_counter ; 

__attribute__((used)) static inline void _trng_hwrng_read(u8 *buf, size_t len)
{
	cpacf_trng(NULL, 0, buf, len);
	atomic64_add(len, &trng_hwrng_counter);
}