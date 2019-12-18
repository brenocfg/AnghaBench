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
struct TYPE_2__ {scalar_t__ media_type; } ;
struct e1000_hw {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_ALGNERRC ; 
 int /*<<< orphan*/  E1000_CBRMPC ; 
 int /*<<< orphan*/  E1000_CBTMPC ; 
 int /*<<< orphan*/  E1000_CEXTERR ; 
 int /*<<< orphan*/  E1000_HGORCH ; 
 int /*<<< orphan*/  E1000_HGORCL ; 
 int /*<<< orphan*/  E1000_HGOTCH ; 
 int /*<<< orphan*/  E1000_HGOTCL ; 
 int /*<<< orphan*/  E1000_HGPTC ; 
 int /*<<< orphan*/  E1000_HTCBDPC ; 
 int /*<<< orphan*/  E1000_HTDPMC ; 
 int /*<<< orphan*/  E1000_IAC ; 
 int /*<<< orphan*/  E1000_ICRXATC ; 
 int /*<<< orphan*/  E1000_ICRXDMTC ; 
 int /*<<< orphan*/  E1000_ICRXOC ; 
 int /*<<< orphan*/  E1000_ICRXPTC ; 
 int /*<<< orphan*/  E1000_ICTXATC ; 
 int /*<<< orphan*/  E1000_ICTXPTC ; 
 int /*<<< orphan*/  E1000_ICTXQEC ; 
 int /*<<< orphan*/  E1000_ICTXQMTC ; 
 int /*<<< orphan*/  E1000_LENERRS ; 
 int /*<<< orphan*/  E1000_MGTPDC ; 
 int /*<<< orphan*/  E1000_MGTPRC ; 
 int /*<<< orphan*/  E1000_MGTPTC ; 
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
 int /*<<< orphan*/  E1000_RPTHC ; 
 int /*<<< orphan*/  E1000_RXERRC ; 
 int /*<<< orphan*/  E1000_SCVPC ; 
 int /*<<< orphan*/  E1000_TNCRS ; 
 int /*<<< orphan*/  E1000_TSCTC ; 
 int /*<<< orphan*/  E1000_TSCTFC ; 
 int /*<<< orphan*/  e1000_clear_hw_cntrs_base_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_sgmii_active_82575 (struct e1000_hw*) ; 

__attribute__((used)) static void e1000_clear_hw_cntrs_82575(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_clear_hw_cntrs_82575");

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

	E1000_READ_REG(hw, E1000_ALGNERRC);
	E1000_READ_REG(hw, E1000_RXERRC);
	E1000_READ_REG(hw, E1000_TNCRS);
	E1000_READ_REG(hw, E1000_CEXTERR);
	E1000_READ_REG(hw, E1000_TSCTC);
	E1000_READ_REG(hw, E1000_TSCTFC);

	E1000_READ_REG(hw, E1000_MGTPRC);
	E1000_READ_REG(hw, E1000_MGTPDC);
	E1000_READ_REG(hw, E1000_MGTPTC);

	E1000_READ_REG(hw, E1000_IAC);
	E1000_READ_REG(hw, E1000_ICRXOC);

	E1000_READ_REG(hw, E1000_ICRXPTC);
	E1000_READ_REG(hw, E1000_ICRXATC);
	E1000_READ_REG(hw, E1000_ICTXPTC);
	E1000_READ_REG(hw, E1000_ICTXATC);
	E1000_READ_REG(hw, E1000_ICTXQEC);
	E1000_READ_REG(hw, E1000_ICTXQMTC);
	E1000_READ_REG(hw, E1000_ICRXDMTC);

	E1000_READ_REG(hw, E1000_CBTMPC);
	E1000_READ_REG(hw, E1000_HTDPMC);
	E1000_READ_REG(hw, E1000_CBRMPC);
	E1000_READ_REG(hw, E1000_RPTHC);
	E1000_READ_REG(hw, E1000_HGPTC);
	E1000_READ_REG(hw, E1000_HTCBDPC);
	E1000_READ_REG(hw, E1000_HGORCL);
	E1000_READ_REG(hw, E1000_HGORCH);
	E1000_READ_REG(hw, E1000_HGOTCL);
	E1000_READ_REG(hw, E1000_HGOTCH);
	E1000_READ_REG(hw, E1000_LENERRS);

	/* This register should not be read in copper configurations */
	if ((hw->phy.media_type == e1000_media_type_internal_serdes) ||
	    e1000_sgmii_active_82575(hw))
		E1000_READ_REG(hw, E1000_SCVPC);
}