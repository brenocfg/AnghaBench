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
typedef  int u32 ;

/* Variables and functions */
 int MOVE_OFFSET_MASK ; 
 int MOVE_OFFSET_SHIFT ; 
 int caam32_to_cpu (int) ; 
 int cpu_to_caam32 (int) ; 
 int desc_len (int* const) ; 

__attribute__((used)) static inline void set_move_tgt_here(u32 * const desc, u32 *move_cmd)
{
	u32 val = caam32_to_cpu(*move_cmd);

	val &= ~MOVE_OFFSET_MASK;
	val |= (desc_len(desc) << (MOVE_OFFSET_SHIFT + 2)) & MOVE_OFFSET_MASK;
	*move_cmd = cpu_to_caam32(val);
}