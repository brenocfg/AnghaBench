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

/* Variables and functions */
 int /*<<< orphan*/  FUNCTIONS_DOMAIN ; 
 int /*<<< orphan*/  symtab_symbol_info (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
functions_info (char *regexp, int from_tty)
{
  symtab_symbol_info (regexp, FUNCTIONS_DOMAIN, from_tty);
}