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
 void* mmalloc (void*,size_t) ; 
 int /*<<< orphan*/  nomem (size_t) ; 

void *
xmmalloc (void *md, size_t size)
{
  void *val;

  /* See libiberty/xmalloc.c.  This function need's to match that's
     semantics.  It never returns NULL.  */
  if (size == 0)
    size = 1;

  val = mmalloc (md, size);
  if (val == NULL)
    nomem (size);

  return (val);
}