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
struct obstack {int dummy; } ;

/* Variables and functions */
 scalar_t__ obstack_alloc (struct obstack*,int) ; 

char *
obsavestring (const char *ptr, int size, struct obstack *obstackp)
{
  char *p = (char *) obstack_alloc (obstackp, size + 1);
  /* Open-coded memcpy--saves function call time.  These strings are usually
     short.  FIXME: Is this really still true with a compiler that can
     inline memcpy? */
  {
    const char *p1 = ptr;
    char *p2 = p;
    const char *end = ptr + size;
    while (p1 != end)
      *p2++ = *p1++;
  }
  p[size] = 0;
  return p;
}