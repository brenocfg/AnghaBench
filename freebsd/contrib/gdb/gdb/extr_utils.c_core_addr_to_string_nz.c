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
typedef  int /*<<< orphan*/  addr ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 char* get_cell () ; 
 int /*<<< orphan*/  phex_nz (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *
core_addr_to_string_nz (const CORE_ADDR addr)
{
  char *str = get_cell ();
  strcpy (str, "0x");
  strcat (str, phex_nz (addr, sizeof (addr)));
  return str;
}