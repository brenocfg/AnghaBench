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
typedef  int /*<<< orphan*/  u32 ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_DBG (char*,size_t) ; 
 int /*<<< orphan*/  _trng_hwrng_read (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int trng_hwrng_data_read(struct hwrng *rng, u32 *data)
{
	size_t len = sizeof(*data);

	_trng_hwrng_read((u8 *) data, len);

	DEBUG_DBG("trng_hwrng_data_read()=%zu\n", len);

	return len;
}