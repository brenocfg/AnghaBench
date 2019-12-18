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
struct TYPE_3__ {int len; struct TYPE_3__* next; struct TYPE_3__* children; scalar_t__ is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int apr_size_t ;

/* Variables and functions */

__attribute__((used)) static apr_size_t
estimate_unparsed_size(const svn_skel_t *skel)
{
  if (skel->is_atom)
    {
      if (skel->len < 100)
        /* If we have to use the explicit-length form, that'll be
           two bytes for the length, one byte for the space, and
           the contents.  */
        return skel->len + 3;
      else
        return skel->len + 30;
    }
  else
    {
      apr_size_t total_len;
      svn_skel_t *child;

      /* Allow space for opening and closing parens, and a space
         between each pair of elements.  */
      total_len = 2;
      for (child = skel->children; child; child = child->next)
        total_len += estimate_unparsed_size(child) + 1;

      return total_len;
    }
}