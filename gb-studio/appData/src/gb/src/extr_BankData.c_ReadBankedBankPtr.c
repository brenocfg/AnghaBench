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
typedef  int /*<<< orphan*/  UBYTE ;
typedef  unsigned char BANK_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  POP_BANK ; 
 int /*<<< orphan*/  PUSH_BANK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

void ReadBankedBankPtr(UBYTE bank, BANK_PTR *to, unsigned char *from)
{
  BANK_PTR bank_ptr;
  // BANK_PTR *bank_ptr_ptr;
  PUSH_BANK(bank);
  // mem_copy

  memcpy(&bank_ptr, from, sizeof(BANK_PTR));

  // bank_ptr_ptr = (BANK_PTR*)ptr;
  // to->bank = bank_ptr_ptr->bank;
  // to->offset = bank_ptr_ptr->offset;
  POP_BANK;

  memcpy(to, &bank_ptr, sizeof(BANK_PTR));
}