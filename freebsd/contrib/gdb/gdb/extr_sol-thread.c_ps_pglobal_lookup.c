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
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;
typedef  int /*<<< orphan*/  gdb_ps_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS_NOSYM ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct minimal_symbol* lookup_minimal_symbol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ps_err_e
ps_pglobal_lookup (gdb_ps_prochandle_t ph, const char *ld_object_name,
		   const char *ld_symbol_name, gdb_ps_addr_t * ld_symbol_addr)
{
  struct minimal_symbol *ms;

  ms = lookup_minimal_symbol (ld_symbol_name, NULL, NULL);

  if (!ms)
    return PS_NOSYM;

  *ld_symbol_addr = SYMBOL_VALUE_ADDRESS (ms);

  return PS_OK;
}