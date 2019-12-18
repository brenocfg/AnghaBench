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
typedef  int UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  POP_BANK ; 
 int /*<<< orphan*/  PUSH_BANK (int) ; 

UWORD ReadBankedUWORD(UBYTE bank, unsigned char *ptr)
{
  UWORD value;
  UBYTE hi, lo;
  PUSH_BANK(bank);
  hi = *(UBYTE *)ptr;
  lo = *(UBYTE *)(ptr + 1);
  value = (hi * 0xFFu) + lo;
  POP_BANK;
  return value;
}