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
 int /*<<< orphan*/  xfree (struct cpstack*) ; 

__attribute__((used)) static char *
cppop (struct cpstack **pstack)
{
  struct cpstack *s;
  char *v;

  if ((*pstack)->name == NULL && (*pstack)->next == NULL)
    return NULL;

  s = *pstack;
  v = s->name;
  *pstack = (*pstack)->next;
  xfree (s);

  return v;
}