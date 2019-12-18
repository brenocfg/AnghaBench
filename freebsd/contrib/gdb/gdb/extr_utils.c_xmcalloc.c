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

/* Variables and functions */
 void* mcalloc (void*,size_t,size_t) ; 
 int /*<<< orphan*/  nomem (size_t) ; 

void *
xmcalloc (void *md, size_t number, size_t size)
{
  void *mem;

  /* See libiberty/xmalloc.c.  This function need's to match that's
     semantics.  It never returns NULL.  */
  if (number == 0 || size == 0)
    {
      number = 1;
      size = 1;
    }

  mem = mcalloc (md, number, size);
  if (mem == NULL)
    nomem (number * size);

  return mem;
}