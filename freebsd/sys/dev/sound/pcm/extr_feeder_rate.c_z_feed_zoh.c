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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct z_info {int z_start; int channels; int bps; int /*<<< orphan*/ * z_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  z_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
z_feed_zoh(struct z_info *info, uint8_t *dst)
{
#if 0
	z_copy(info->z_delay +
	    (info->z_start * info->channels * info->bps), dst,
	    info->channels * info->bps);
#else
	uint32_t cnt;
	uint8_t *src;

	cnt = info->channels * info->bps;
	src = info->z_delay + (info->z_start * cnt);

	/*
	 * This is a bit faster than doing bcopy() since we're dealing
	 * with possible unaligned samples.
	 */
	do {
		*dst++ = *src++;
	} while (--cnt != 0);
#endif
}