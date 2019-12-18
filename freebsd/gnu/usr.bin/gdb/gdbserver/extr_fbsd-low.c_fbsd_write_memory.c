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
typedef  int /*<<< orphan*/  PTRACE_XFER_TYPE ;
typedef  int /*<<< orphan*/  PTRACE_ARG3_TYPE ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PT_READ_D ; 
 int /*<<< orphan*/  PT_WRITE_D ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ debug_threads ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int,long) ; 
 int /*<<< orphan*/  inferior_pid ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
fbsd_write_memory (CORE_ADDR memaddr, const char *myaddr, int len)
{
  register int i;
  /* Round starting address down to longword boundary.  */
  register CORE_ADDR addr = memaddr & -(CORE_ADDR) sizeof (PTRACE_XFER_TYPE);
  /* Round ending address up; get number of longwords that makes.  */
  register int count
  = (((memaddr + len) - addr) + sizeof (PTRACE_XFER_TYPE) - 1) / sizeof (PTRACE_XFER_TYPE);
  /* Allocate buffer of that many longwords.  */
  register PTRACE_XFER_TYPE *buffer = (PTRACE_XFER_TYPE *) alloca (count * sizeof (PTRACE_XFER_TYPE));
  extern int errno;

  if (debug_threads)
    {
      fprintf (stderr, "Writing %02x to %08lx\n", (unsigned)myaddr[0], (long)memaddr);
    }

  /* Fill start and end extra bytes of buffer with existing memory data.  */

  buffer[0] = ptrace (PT_READ_D, inferior_pid,
		      (PTRACE_ARG3_TYPE) (intptr_t)addr, 0);

  if (count > 1)
    {
      buffer[count - 1]
	= ptrace (PT_READ_D, inferior_pid,
		  (PTRACE_ARG3_TYPE) (intptr_t) (addr + (count - 1)
				      * sizeof (PTRACE_XFER_TYPE)),
		  0);
    }

  /* Copy data to be written over corresponding part of buffer */

  memcpy ((char *) buffer + (memaddr & (sizeof (PTRACE_XFER_TYPE) - 1)), myaddr, len);

  /* Write the entire buffer.  */

  for (i = 0; i < count; i++, addr += sizeof (PTRACE_XFER_TYPE))
    {
      errno = 0;
      ptrace (PT_WRITE_D, inferior_pid, (PTRACE_ARG3_TYPE) (intptr_t)addr, buffer[i]);
      if (errno)
	return errno;
    }

  return 0;
}