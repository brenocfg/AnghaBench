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
 int errno ; 
 struct mem_region* lookup_mem_region (scalar_t__) ; 
 int /*<<< orphan*/  target_dcache ; 

__attribute__((used)) static int
target_xfer_memory_partial (CORE_ADDR memaddr, char *myaddr, int len,
			    int write_p, int *err)
{
  int res;
  int reg_len;
  struct mem_region *region;

  /* Zero length requests are ok and require no work.  */
  if (len == 0)
    {
      *err = 0;
      return 0;
    }

  region = lookup_mem_region(memaddr);
  if (memaddr + len < region->hi)
    reg_len = len;
  else
    reg_len = region->hi - memaddr;

  switch (region->attrib.mode)
    {
    case MEM_RO:
      if (write_p)
	{
	  *err = EIO;
	  return -1;
	}
      break;

    case MEM_WO:
      if (write_p)
	{
	  *err = EIO;
	  return -1;
	}
      break;
    }

  if (region->attrib.cache)
    res = dcache_xfer_memory (target_dcache, memaddr, myaddr,
			      reg_len, write_p);
  else
    res = do_xfer_memory (memaddr, myaddr, reg_len, write_p,
			  &region->attrib);
      
  if (res <= 0)
    {
      if (errno != 0)
	*err = errno;
      else
	*err = EIO;

        return -1;
    }

  *err = 0;
  return res;
}