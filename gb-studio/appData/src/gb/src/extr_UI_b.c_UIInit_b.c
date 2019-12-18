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
typedef  scalar_t__ UWORD ;

/* Variables and functions */
 size_t CURSOR_BANK ; 
 scalar_t__ CURSOR_BANK_OFFSET ; 
 size_t FRAME_BANK ; 
 scalar_t__ FRAME_BANK_OFFSET ; 
 int /*<<< orphan*/  SetBankedBkgData (size_t,int,int,scalar_t__) ; 
 int /*<<< orphan*/  UISetPos (int,int) ; 
 scalar_t__* bank_data_ptrs ; 
 int /*<<< orphan*/  set_bkg_data (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_black ; 
 int /*<<< orphan*/  ui_white ; 

void UIInit_b()
{
  UWORD ptr;

  UISetPos(160, 144);

  // Load frame tiles from data bank
  ptr = ((UWORD)bank_data_ptrs[FRAME_BANK]) + FRAME_BANK_OFFSET;
  SetBankedBkgData(FRAME_BANK, 192, 9, ptr);

  set_bkg_data(0xC9, 1, ui_white);
  set_bkg_data(0xCA, 1, ui_black);

  ptr = ((UWORD)bank_data_ptrs[CURSOR_BANK]) + CURSOR_BANK_OFFSET;
  SetBankedBkgData(FRAME_BANK, 0xCB, 1, ptr);
}