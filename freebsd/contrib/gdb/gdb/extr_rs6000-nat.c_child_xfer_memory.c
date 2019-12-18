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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int ARCH64 () ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_WRITE_D ; 
 int /*<<< orphan*/  QUIT ; 
 scalar_t__ alloca (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  read_word (int,int*,int) ; 
 int /*<<< orphan*/  rs6000_ptrace32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rs6000_ptrace64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int
child_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len,
		   int write, struct mem_attrib *attrib,
		   struct target_ops *target)
{
  /* Round starting address down to 32-bit word boundary. */
  int mask = sizeof (int) - 1;
  CORE_ADDR addr = memaddr & ~(CORE_ADDR)mask;

  /* Round ending address up to 32-bit word boundary. */
  int count = ((memaddr + len - addr + mask) & ~(CORE_ADDR)mask)
    / sizeof (int);

  /* Allocate word transfer buffer. */
  /* FIXME (alloca): This code, cloned from infptrace.c, is unsafe
     because it uses alloca to allocate a buffer of arbitrary size.
     For very large xfers, this could crash GDB's stack.  */
  int *buf = (int *) alloca (count * sizeof (int));

  int arch64 = ARCH64 ();
  int i;

  if (!write)
    {
      /* Retrieve memory a word at a time. */
      for (i = 0; i < count; i++, addr += sizeof (int))
	{
	  if (!read_word (addr, buf + i, arch64))
	    return 0;
	  QUIT;
	}

      /* Copy memory to supplied buffer. */
      addr -= count * sizeof (int);
      memcpy (myaddr, (char *)buf + (memaddr - addr), len);
    }
  else
    {
      /* Fetch leading memory needed for alignment. */
      if (addr < memaddr)
	if (!read_word (addr, buf, arch64))
	  return 0;

      /* Fetch trailing memory needed for alignment. */
      if (addr + count * sizeof (int) > memaddr + len)
	if (!read_word (addr + (count - 1) * sizeof (int),
                        buf + count - 1, arch64))
	  return 0;

      /* Copy supplied data into memory buffer. */
      memcpy ((char *)buf + (memaddr - addr), myaddr, len);

      /* Store memory one word at a time. */
      for (i = 0, errno = 0; i < count; i++, addr += sizeof (int))
	{
	  if (arch64)
	    rs6000_ptrace64 (PT_WRITE_D, PIDGET (inferior_ptid), addr, buf[i], NULL);
	  else
	    rs6000_ptrace32 (PT_WRITE_D, PIDGET (inferior_ptid), (int *)(long) addr,
		      buf[i], NULL);

	  if (errno)
	    return 0;
	  QUIT;
	}
    }

  return len;
}