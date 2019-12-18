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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 unsigned int DLD_FLAGS_HOOKVALID ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 unsigned int extract_unsigned_integer (char*,int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 struct cleanup* save_inferior_ptid () ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,unsigned int) ; 
 int target_read_memory (int /*<<< orphan*/ ,char*,int) ; 
 int target_write_memory (int /*<<< orphan*/ ,char*,int) ; 

void
som_solib_remove_inferior_hook (int pid)
{
  CORE_ADDR addr;
  struct minimal_symbol *msymbol;
  int status;
  char dld_flags_buffer[4];
  unsigned int dld_flags_value;
  struct cleanup *old_cleanups = save_inferior_ptid ();

  /* Ensure that we're really operating on the specified process. */
  inferior_ptid = pid_to_ptid (pid);

  /* We won't bother to remove the solib breakpoints from this process.

     In fact, on PA64 the breakpoint is hard-coded into the dld callback,
     and thus we're not supposed to remove it.

     Rather, we'll merely clear the dld_flags bit that enables callbacks.
   */
  msymbol = lookup_minimal_symbol ("__dld_flags", NULL, NULL);

  addr = SYMBOL_VALUE_ADDRESS (msymbol);
  status = target_read_memory (addr, dld_flags_buffer, 4);

  dld_flags_value = extract_unsigned_integer (dld_flags_buffer, 4);

  dld_flags_value &= ~DLD_FLAGS_HOOKVALID;
  store_unsigned_integer (dld_flags_buffer, 4, dld_flags_value);
  status = target_write_memory (addr, dld_flags_buffer, 4);

  do_cleanups (old_cleanups);
}