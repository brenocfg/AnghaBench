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
struct tree {scalar_t__ label; struct tree* rlink; struct tree* llink; } ;

/* Variables and functions */

__attribute__((used)) static int
hasevery (register struct tree const *a, register struct tree const *b)
{
  if (!b)
    return 1;
  if (!hasevery(a, b->llink))
    return 0;
  if (!hasevery(a, b->rlink))
    return 0;
  while (a && b->label != a->label)
    if (b->label < a->label)
      a = a->llink;
    else
      a = a->rlink;
  return !!a;
}