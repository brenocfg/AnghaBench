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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_block_cache {int dummy; } ;
struct pt_bcache_entry {int ninsn; int mode; int /*<<< orphan*/  qualifier; } ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;
typedef  int /*<<< orphan*/  bce ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_bcache_entry*,int /*<<< orphan*/ ,int) ; 
 int pt_bcache_add (struct pt_block_cache*,int /*<<< orphan*/ ,struct pt_bcache_entry) ; 
 int /*<<< orphan*/  ptbq_decode ; 

__attribute__((used)) static inline int pt_blk_add_decode(struct pt_block_cache *bcache,
				    uint64_t ioff, enum pt_exec_mode mode)
{
	struct pt_bcache_entry bce;

	memset(&bce, 0, sizeof(bce));
	bce.ninsn = 1;
	bce.mode = mode;
	bce.qualifier = ptbq_decode;

	return pt_bcache_add(bcache, ioff, bce);
}