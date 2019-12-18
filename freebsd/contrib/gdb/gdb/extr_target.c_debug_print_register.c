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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 int MAX_REGISTER_SIZE ; 
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 char* REGISTER_NAME (int) ; 
 int /*<<< orphan*/  deprecated_read_register_gen (int,unsigned char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  paddr_d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_register (int) ; 

__attribute__((used)) static void
debug_print_register (const char * func, int regno)
{
  fprintf_unfiltered (gdb_stdlog, "%s ", func);
  if (regno >= 0 && regno < NUM_REGS + NUM_PSEUDO_REGS
      && REGISTER_NAME (regno) != NULL && REGISTER_NAME (regno)[0] != '\0')
    fprintf_unfiltered (gdb_stdlog, "(%s)", REGISTER_NAME (regno));
  else
    fprintf_unfiltered (gdb_stdlog, "(%d)", regno);
  if (regno >= 0)
    {
      int i;
      unsigned char buf[MAX_REGISTER_SIZE];
      deprecated_read_register_gen (regno, buf);
      fprintf_unfiltered (gdb_stdlog, " = ");
      for (i = 0; i < DEPRECATED_REGISTER_RAW_SIZE (regno); i++)
	{
	  fprintf_unfiltered (gdb_stdlog, "%02x", buf[i]);
	}
      if (DEPRECATED_REGISTER_RAW_SIZE (regno) <= sizeof (LONGEST))
	{
	  fprintf_unfiltered (gdb_stdlog, " 0x%s %s",
			      paddr_nz (read_register (regno)),
			      paddr_d (read_register (regno)));
	}
    }
  fprintf_unfiltered (gdb_stdlog, "\n");
}