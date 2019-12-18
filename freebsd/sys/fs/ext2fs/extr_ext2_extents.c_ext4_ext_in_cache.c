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
struct ext4_extent_cache {int ec_type; scalar_t__ ec_blk; scalar_t__ ec_len; int ec_start; } ;
struct inode {struct ext4_extent_cache i_ext_cache; } ;
struct ext4_extent {scalar_t__ e_blk; int e_start_lo; int e_start_hi; scalar_t__ e_len; } ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */
 int EXT4_EXT_CACHE_NO ; 

int
ext4_ext_in_cache(struct inode *ip, daddr_t lbn, struct ext4_extent *ep)
{
	struct ext4_extent_cache *ecp;
	int ret = EXT4_EXT_CACHE_NO;

	ecp = &ip->i_ext_cache;
	if (ecp->ec_type == EXT4_EXT_CACHE_NO)
		return (ret);

	if (lbn >= ecp->ec_blk && lbn < ecp->ec_blk + ecp->ec_len) {
		ep->e_blk = ecp->ec_blk;
		ep->e_start_lo = ecp->ec_start & 0xffffffff;
		ep->e_start_hi = ecp->ec_start >> 32 & 0xffff;
		ep->e_len = ecp->ec_len;
		ret = ecp->ec_type;
	}
	return (ret);
}