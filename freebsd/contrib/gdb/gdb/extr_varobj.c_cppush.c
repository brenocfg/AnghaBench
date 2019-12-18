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
struct cpstack {char* name; struct cpstack* next; } ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
cppush (struct cpstack **pstack, char *name)
{
  struct cpstack *s;

  s = (struct cpstack *) xmalloc (sizeof (struct cpstack));
  s->name = name;
  s->next = *pstack;
  *pstack = s;
}