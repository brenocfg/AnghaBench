#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* children; int /*<<< orphan*/  is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 

void svn_skel__append(svn_skel_t *list_skel, svn_skel_t *skel)
{
  SVN_ERR_ASSERT_NO_RETURN(list_skel != NULL && !list_skel->is_atom);

  if (list_skel->children == NULL)
    {
      list_skel->children = skel;
    }
  else
    {
      list_skel = list_skel->children;
      while (list_skel->next != NULL)
        list_skel = list_skel->next;
      list_skel->next = skel;
    }
}