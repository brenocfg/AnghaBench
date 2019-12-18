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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 scalar_t__ NFHD_GET_CAPACITY ; 
 int /*<<< orphan*/  nf_call (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfhd_id ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline s32 nfhd_get_capacity(u32 major, u32 minor, u32 *blocks,
				    u32 *blocksize)
{
	return nf_call(nfhd_id + NFHD_GET_CAPACITY, major, minor,
		       virt_to_phys(blocks), virt_to_phys(blocksize));
}