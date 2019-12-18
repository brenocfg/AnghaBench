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
struct TYPE_4__ {struct TYPE_4__* children; struct TYPE_4__* next; int /*<<< orphan*/  is_atom; } ;
typedef  TYPE_1__ svn_skel_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int) ; 

void
svn_skel__prepend(svn_skel_t *skel, svn_skel_t *list_skel)
{
  /* If list_skel isn't even a list, somebody's not using this
     function properly. */
  SVN_ERR_ASSERT_NO_RETURN(! list_skel->is_atom);

  skel->next = list_skel->children;
  list_skel->children = skel;
}