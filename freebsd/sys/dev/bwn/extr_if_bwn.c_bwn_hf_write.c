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
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_SHARED_HFHI ; 
 int /*<<< orphan*/  BWN_SHARED_HFLO ; 
 int /*<<< orphan*/  BWN_SHARED_HFMI ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
bwn_hf_write(struct bwn_mac *mac, uint64_t value)
{

	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHARED_HFLO,
	    (value & 0x00000000ffffull));
	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHARED_HFMI,
	    (value & 0x0000ffff0000ull) >> 16);
	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHARED_HFHI,
	    (value & 0xffff00000000ULL) >> 32);
}