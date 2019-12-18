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
struct regset_info {scalar_t__ size; int /*<<< orphan*/  (* store_function ) (void*) ;int /*<<< orphan*/  get_request; } ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;

/* Variables and functions */
 int inferior_pid ; 
 void* malloc (scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 struct regset_info* target_regsets ; 

__attribute__((used)) static int
regsets_fetch_inferior_registers ()
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
      res = ptrace (regset->get_request, inferior_pid, (PTRACE_ARG3_TYPE) buf, 0);
      if (res < 0)
	{
	  char s[256];
	  sprintf (s, "ptrace(regsets_fetch_inferior_registers) PID=%d",
		   inferior_pid);
	  perror (s);
	}
      regset->store_function (buf);
      regset ++;
    }
  return 0;
}