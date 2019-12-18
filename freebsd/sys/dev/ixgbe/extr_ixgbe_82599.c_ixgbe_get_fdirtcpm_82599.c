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
struct TYPE_2__ {int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_port; } ;
union ixgbe_atr_input {TYPE_1__ formatted; } ;
typedef  int u32 ;

/* Variables and functions */
 int IXGBE_FDIRTCPM_DPORTM_SHIFT ; 
 int IXGBE_NTOHS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ixgbe_get_fdirtcpm_82599(union ixgbe_atr_input *input_mask)
{
	u32 mask = IXGBE_NTOHS(input_mask->formatted.dst_port);
	mask <<= IXGBE_FDIRTCPM_DPORTM_SHIFT;
	mask |= IXGBE_NTOHS(input_mask->formatted.src_port);
	mask = ((mask & 0x55555555) << 1) | ((mask & 0xAAAAAAAA) >> 1);
	mask = ((mask & 0x33333333) << 2) | ((mask & 0xCCCCCCCC) >> 2);
	mask = ((mask & 0x0F0F0F0F) << 4) | ((mask & 0xF0F0F0F0) >> 4);
	return ((mask & 0x00FF00FF) << 8) | ((mask & 0xFF00FF00) >> 8);
}