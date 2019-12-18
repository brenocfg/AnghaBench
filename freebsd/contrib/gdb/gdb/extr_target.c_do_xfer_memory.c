#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int (* to_xfer_memory ) (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ;scalar_t__ to_has_all_memory; int /*<<< orphan*/  to_has_memory; struct target_ops* beneath; } ;
struct section_table {int /*<<< orphan*/  the_bfd_section; int /*<<< orphan*/  bfd; } ;
struct mem_attrib {int dummy; } ;
struct TYPE_5__ {int (* to_xfer_memory ) (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int SEC_READONLY ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ current_target ; 
 scalar_t__ errno ; 
 int stub1 (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,TYPE_1__*) ; 
 int stub2 (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ; 
 struct section_table* target_section_by_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct target_ops* target_stack ; 
 scalar_t__ trust_readonly ; 
 int xfer_memory (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct mem_attrib*,TYPE_1__*) ; 

int
do_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		struct mem_attrib *attrib)
{
  int res;
  int done = 0;
  struct target_ops *t;

  /* Zero length requests are ok and require no work.  */
  if (len == 0)
    return 0;

  /* to_xfer_memory is not guaranteed to set errno, even when it returns
     0.  */
  errno = 0;

  if (!write && trust_readonly)
    {
      struct section_table *secp;
      /* User-settable option, "trust-readonly-sections".  If true,
         then memory from any SEC_READONLY bfd section may be read
         directly from the bfd file.  */
      secp = target_section_by_addr (&current_target, memaddr);
      if (secp != NULL
	  && (bfd_get_section_flags (secp->bfd, secp->the_bfd_section)
	      & SEC_READONLY))
	return xfer_memory (memaddr, myaddr, len, 0, attrib, &current_target);
    }

  /* The quick case is that the top target can handle the transfer.  */
  res = current_target.to_xfer_memory
    (memaddr, myaddr, len, write, attrib, &current_target);

  /* If res <= 0 then we call it again in the loop.  Ah well. */
  if (res <= 0)
    {
      for (t = target_stack; t != NULL; t = t->beneath)
	{
	  if (!t->to_has_memory)
	    continue;

	  res = t->to_xfer_memory (memaddr, myaddr, len, write, attrib, t);
	  if (res > 0)
	    break;		/* Handled all or part of xfer */
	  if (t->to_has_all_memory)
	    break;
	}

      if (res <= 0)
	return -1;
    }

  return res;
}