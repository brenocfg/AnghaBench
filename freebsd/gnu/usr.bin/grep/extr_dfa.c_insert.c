#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nelem; TYPE_2__* elems; } ;
typedef  TYPE_1__ position_set ;
struct TYPE_6__ {scalar_t__ index; int /*<<< orphan*/  constraint; } ;
typedef  TYPE_2__ position ;

/* Variables and functions */

__attribute__((used)) static void
insert (position p, position_set *s)
{
  int i;
  position t1, t2;

  for (i = 0; i < s->nelem && p.index < s->elems[i].index; ++i)
    continue;
  if (i < s->nelem && p.index == s->elems[i].index)
    s->elems[i].constraint |= p.constraint;
  else
    {
      t1 = p;
      ++s->nelem;
      while (i < s->nelem)
	{
	  t2 = s->elems[i];
	  s->elems[i++] = t1;
	  t1 = t2;
	}
    }
}