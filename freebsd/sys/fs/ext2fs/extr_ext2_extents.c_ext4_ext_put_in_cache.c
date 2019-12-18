#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int ec_type; scalar_t__ ec_start; scalar_t__ ec_len; scalar_t__ ec_blk; } ;
struct inode {TYPE_1__ i_ext_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static inline void
ext4_ext_put_in_cache(struct inode *ip, uint32_t blk,
			uint32_t len, uint32_t start, int type)
{

	KASSERT(len != 0, ("ext4_ext_put_in_cache: bad input"));

	ip->i_ext_cache.ec_type = type;
	ip->i_ext_cache.ec_blk = blk;
	ip->i_ext_cache.ec_len = len;
	ip->i_ext_cache.ec_start = start;
}