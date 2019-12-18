#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; scalar_t__ cache; } ;
struct mem_region {scalar_t__ hi; TYPE_1__ attrib; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int EIO ; 
#define  MEM_RO 129 
#define  MEM_WO 128 
 int dcache_xfer_memory (int /*<<< orphan*/ ,scalar_t__,char*,int,int) ; 
 int do_xfer_memory (scalar_t__,char*,int,int,TYPE_1__*) ; 
 scalar_t__ errno ; 
 struct mem_region* lookup_mem_region (scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  target_dcache ; 

__attribute__((used)) static int
target_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write)
{
  int res;
  int reg_len;
  struct mem_region *region;

  /* Zero length requests are ok and require no work.  */
  if (len == 0)
    {
      return 0;
    }

  while (len > 0)
    {
      region = lookup_mem_region(memaddr);
      if (memaddr + len < region->hi)
	reg_len = len;
      else
	reg_len = region->hi - memaddr;

      switch (region->attrib.mode)
	{
	case MEM_RO:
	  if (write)
	    return EIO;
	  break;
	  
	case MEM_WO:
	  if (!write)
	    return EIO;
	  break;
	}

      while (reg_len > 0)
	{
	  if (region->attrib.cache)
	    res = dcache_xfer_memory (target_dcache, memaddr, myaddr,
				     reg_len, write);
	  else
	    res = do_xfer_memory (memaddr, myaddr, reg_len, write,
				 &region->attrib);
	      
	  if (res <= 0)
	    {
	      /* If this address is for nonexistent memory, read zeros
		 if reading, or do nothing if writing.  Return
		 error. */
	      if (!write)
		memset (myaddr, 0, len);
	      if (errno == 0)
		return EIO;
	      else
		return errno;
	    }

	  memaddr += res;
	  myaddr  += res;
	  len     -= res;
	  reg_len -= res;
	}
    }
  
  return 0;			/* We managed to cover it all somehow. */
}