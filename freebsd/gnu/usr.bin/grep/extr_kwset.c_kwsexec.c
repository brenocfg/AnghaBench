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
struct kwsmatch {size_t* offset; int /*<<< orphan*/ * size; scalar_t__ index; } ;
struct kwset {int words; scalar_t__ trans; int /*<<< orphan*/  mind; } ;
typedef  scalar_t__ kwset_t ;

/* Variables and functions */
 size_t bmexec (scalar_t__,char const*,size_t) ; 
 size_t cwexec (scalar_t__,char const*,size_t,struct kwsmatch*) ; 

size_t
kwsexec (kwset_t kws, char const *text, size_t size,
	 struct kwsmatch *kwsmatch)
{
  struct kwset const *kwset = (struct kwset *) kws;
  if (kwset->words == 1 && kwset->trans == 0)
    {
      size_t ret = bmexec (kws, text, size);
      if (kwsmatch != 0 && ret != (size_t) -1)
	{
	  kwsmatch->index = 0;
	  kwsmatch->offset[0] = ret;
	  kwsmatch->size[0] = kwset->mind;
	}
      return ret;
    }
  else
    return cwexec(kws, text, size, kwsmatch);
}