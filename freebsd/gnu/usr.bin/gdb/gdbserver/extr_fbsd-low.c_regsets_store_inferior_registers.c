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
struct regset_info {scalar_t__ size; int /*<<< orphan*/  set_request; int /*<<< orphan*/  (* fill_function ) (void*) ;} ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  inferior_pid ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 struct regset_info* target_regsets ; 

__attribute__((used)) static int
regsets_store_inferior_registers ()
{
  struct regset_info *regset;

  regset = target_regsets;

  while (regset->size >= 0)
    {
      void *buf;
      int res;

      if (regset->size == 0)
	{
	  regset ++;
	  continue;
	}

      buf = malloc (regset->size);
      regset->fill_function (buf);
      res = ptrace (regset->set_request, inferior_pid, (PTRACE_ARG3_TYPE) buf, 0);
      if (res < 0)
	{
	  perror ("Warning: ptrace(regsets_store_inferior_registers)");
	}
      regset ++;
      free (buf);
    }
  return 0;
}