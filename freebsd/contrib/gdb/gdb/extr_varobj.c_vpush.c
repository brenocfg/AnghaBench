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
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
vpush (struct vstack **pstack, struct varobj *var)
{
  struct vstack *s;

  s = (struct vstack *) xmalloc (sizeof (struct vstack));
  s->var = var;
  s->next = *pstack;
  *pstack = s;
}