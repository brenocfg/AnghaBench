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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int target_read_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
partial_memory_read (CORE_ADDR memaddr, char *myaddr, int len, int *errnoptr)
{
  int nread;			/* Number of bytes actually read. */
  int errcode;			/* Error from last read. */

  /* First try a complete read. */
  errcode = target_read_memory (memaddr, myaddr, len);
  if (errcode == 0)
    {
      /* Got it all. */
      nread = len;
    }
  else
    {
      /* Loop, reading one byte at a time until we get as much as we can. */
      for (errcode = 0, nread = 0; len > 0 && errcode == 0; nread++, len--)
	{
	  errcode = target_read_memory (memaddr++, myaddr++, 1);
	}
      /* If an error, the last read was unsuccessful, so adjust count. */
      if (errcode != 0)
	{
	  nread--;
	}
    }
  if (errnoptr != NULL)
    {
      *errnoptr = errcode;
    }
  return (nread);
}