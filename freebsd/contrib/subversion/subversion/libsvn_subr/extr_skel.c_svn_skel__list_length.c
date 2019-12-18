#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* next; struct TYPE_3__* children; scalar_t__ is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;

/* Variables and functions */

int
svn_skel__list_length(const svn_skel_t *skel)
{
  int len = 0;
  const svn_skel_t *child;

  if ((! skel) || skel->is_atom)
    return -1;

  for (child = skel->children; child; child = child->next)
    len++;

  return len;
}