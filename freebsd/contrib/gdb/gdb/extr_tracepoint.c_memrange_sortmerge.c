#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct memrange {int dummy; } ;
struct collection_list {int next_memrange; TYPE_1__* list; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memrange_cmp ; 
 int /*<<< orphan*/  qsort (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
memrange_sortmerge (struct collection_list *memranges)
{
  int a, b;

  qsort (memranges->list, memranges->next_memrange,
	 sizeof (struct memrange), memrange_cmp);
  if (memranges->next_memrange > 0)
    {
      for (a = 0, b = 1; b < memranges->next_memrange; b++)
	{
	  if (memranges->list[a].type == memranges->list[b].type &&
	      memranges->list[b].start - memranges->list[a].end <=
	      MAX_REGISTER_SIZE)
	    {
	      /* memrange b starts before memrange a ends; merge them.  */
	      if (memranges->list[b].end > memranges->list[a].end)
		memranges->list[a].end = memranges->list[b].end;
	      continue;		/* next b, same a */
	    }
	  a++;			/* next a */
	  if (a != b)
	    memcpy (&memranges->list[a], &memranges->list[b],
		    sizeof (struct memrange));
	}
      memranges->next_memrange = a + 1;
    }
}