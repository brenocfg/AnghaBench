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
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  scalar_t__ paddr_t ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PS_NOSYM ; 
 int /*<<< orphan*/  PS_OK ; 
 scalar_t__ look_up_one_symbol (char const*,scalar_t__*) ; 

ps_err_e
ps_pglobal_lookup (gdb_ps_prochandle_t ph, const char *obj,
		   const char *name, paddr_t *sym_addr)
{
  CORE_ADDR addr;

  if (look_up_one_symbol (name, &addr) == 0)
    return PS_NOSYM;

  *sym_addr = (paddr_t) (unsigned long) addr;
  return PS_OK;
}