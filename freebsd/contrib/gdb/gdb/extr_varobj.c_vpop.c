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
struct vstack {struct vstack* next; struct varobj* var; } ;
struct varobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfree (struct vstack*) ; 

__attribute__((used)) static struct varobj *
vpop (struct vstack **pstack)
{
  struct vstack *s;
  struct varobj *v;

  if ((*pstack)->var == NULL && (*pstack)->next == NULL)
    return NULL;

  s = *pstack;
  v = s->var;
  *pstack = (*pstack)->next;
  xfree (s);

  return v;
}