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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct table_info {int dummy; } ;
struct chash_cfg {int items4; int size4; int items6; int size6; } ;

/* Variables and functions */

__attribute__((used)) static int
ta_need_modify_chash(void *ta_state, struct table_info *ti, uint32_t count,
    uint64_t *pflags)
{
	struct chash_cfg *cfg;
	uint64_t data;

	/*
	 * Since we don't know exact number of IPv4/IPv6 records in @count,
	 * ignore non-zero @count value at all. Check current hash sizes
	 * and return appropriate data.
	 */

	cfg = (struct chash_cfg *)ta_state;

	data = 0;
	if (cfg->items4 > cfg->size4 && cfg->size4 < 65536)
		data |= (cfg->size4 * 2) << 16;
	if (cfg->items6 > cfg->size6 && cfg->size6 < 65536)
		data |= cfg->size6 * 2;

	if (data != 0) {
		*pflags = data;
		return (1);
	}

	return (0);
}