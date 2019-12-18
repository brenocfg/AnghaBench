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
struct minimal_symbol {int dummy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_PRINT_NAME (struct minimal_symbol*) ; 
 int SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int TARGET_ADDR_BIT ; 
 char* local_hex_string_custom (int,char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_msymbol_info (struct minimal_symbol *msymbol)
{
  char *tmp;

  if (TARGET_ADDR_BIT <= 32)
    tmp = local_hex_string_custom (SYMBOL_VALUE_ADDRESS (msymbol)
				   & (CORE_ADDR) 0xffffffff,
				   "08l");
  else
    tmp = local_hex_string_custom (SYMBOL_VALUE_ADDRESS (msymbol),
				   "016l");
  printf_filtered ("%s  %s\n",
		   tmp, SYMBOL_PRINT_NAME (msymbol));
}