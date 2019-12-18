#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  is_atom; struct TYPE_5__* children; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_valid_proplist_skel (TYPE_1__*) ; 
 int svn_skel__list_length (TYPE_1__ const*) ; 

__attribute__((used)) static svn_boolean_t
is_valid_iproplist_skel(const svn_skel_t *skel)
{
  int len = svn_skel__list_length(skel);

  if ((len >= 0) && (len & 1) == 0)
    {
      svn_skel_t *elt;

      for (elt = skel->children; elt; elt = elt->next)
        {
          if (!elt->is_atom)
            return FALSE;

          if (elt->next == NULL)
            return FALSE;

          elt = elt->next;

          if (! is_valid_proplist_skel(elt))
            return FALSE;
        }

      return TRUE;
    }

  return FALSE;
}