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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_read_pba_string_generic (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

s32 e1000_read_pba_string(struct e1000_hw *hw, u8 *pba_num, u32 pba_num_size)
{
	return e1000_read_pba_string_generic(hw, pba_num, pba_num_size);
}