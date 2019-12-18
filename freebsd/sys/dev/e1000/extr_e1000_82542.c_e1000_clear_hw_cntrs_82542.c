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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_PRC1023 ; 
 int /*<<< orphan*/  E1000_PRC127 ; 
 int /*<<< orphan*/  E1000_PRC1522 ; 
 int /*<<< orphan*/  E1000_PRC255 ; 
 int /*<<< orphan*/  E1000_PRC511 ; 
 int /*<<< orphan*/  E1000_PRC64 ; 
 int /*<<< orphan*/  E1000_PTC1023 ; 
 int /*<<< orphan*/  E1000_PTC127 ; 
 int /*<<< orphan*/  E1000_PTC1522 ; 
 int /*<<< orphan*/  E1000_PTC255 ; 
 int /*<<< orphan*/  E1000_PTC511 ; 
 int /*<<< orphan*/  E1000_PTC64 ; 
 int /*<<< orphan*/  E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_base_generic (struct e1000_hw*) ; 

__attribute__((used)) static void e1000_clear_hw_cntrs_82542(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_clear_hw_cntrs_82542");

	e1000_clear_hw_cntrs_base_generic(hw);

	E1000_READ_REG(hw, E1000_PRC64);
	E1000_READ_REG(hw, E1000_PRC127);
	E1000_READ_REG(hw, E1000_PRC255);
	E1000_READ_REG(hw, E1000_PRC511);
	E1000_READ_REG(hw, E1000_PRC1023);
	E1000_READ_REG(hw, E1000_PRC1522);
	E1000_READ_REG(hw, E1000_PTC64);
	E1000_READ_REG(hw, E1000_PTC127);
	E1000_READ_REG(hw, E1000_PTC255);
	E1000_READ_REG(hw, E1000_PTC511);
	E1000_READ_REG(hw, E1000_PTC1023);
	E1000_READ_REG(hw, E1000_PTC1522);
}