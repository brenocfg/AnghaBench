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
 int bwn_shm_read_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint64_t
bwn_hf_read(struct bwn_mac *mac)
{
	uint64_t ret;

	ret = bwn_shm_read_2(mac, BWN_SHARED, BWN_SHARED_HFHI);
	ret <<= 16;
	ret |= bwn_shm_read_2(mac, BWN_SHARED, BWN_SHARED_HFMI);
	ret <<= 16;
	ret |= bwn_shm_read_2(mac, BWN_SHARED, BWN_SHARED_HFLO);
	return (ret);
}