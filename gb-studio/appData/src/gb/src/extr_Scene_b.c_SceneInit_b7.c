#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;
struct TYPE_3__ {size_t bank; scalar_t__ offset; } ;
typedef  TYPE_1__ BANK_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_PTRS_BANK ; 
 int /*<<< orphan*/  ReadBankedBankPtr (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadBankedUBYTE (size_t,scalar_t__) ; 
 int /*<<< orphan*/  SetBankedBkgData (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* bank_data_ptrs ; 
 int /*<<< orphan*/ * tileset_bank_ptrs ; 
 size_t tileset_index ; 

void SceneInit_b7()
{
  BANK_PTR tileset_bank_ptr;
  UWORD tileset_ptr;
  UBYTE tileset_size;
  // Load Image Tileset
  ReadBankedBankPtr(DATA_PTRS_BANK, &tileset_bank_ptr, &tileset_bank_ptrs[tileset_index]);
  tileset_ptr = ((UWORD)bank_data_ptrs[tileset_bank_ptr.bank]) + tileset_bank_ptr.offset;
  tileset_size = ReadBankedUBYTE(tileset_bank_ptr.bank, tileset_ptr);
  SetBankedBkgData(tileset_bank_ptr.bank, 0, tileset_size, tileset_ptr + 1u);
}