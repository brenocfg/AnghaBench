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
struct TYPE_5__ {scalar_t__ is_atom; struct TYPE_5__* next; struct TYPE_5__* children; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int svn_skel__list_length (TYPE_1__*) ; 
 scalar_t__ svn_skel__matches_atom (TYPE_1__*,char*) ; 

__attribute__((used)) static svn_boolean_t
is_valid_rep_delta_chunk_skel(svn_skel_t *skel)
{
  int len;
  svn_skel_t *window;
  svn_skel_t *diff;

  /* check the delta skel. */
  if ((svn_skel__list_length(skel) != 2)
      || (! skel->children->is_atom))
    return FALSE;

  /* check the window. */
  window = skel->children->next;
  len = svn_skel__list_length(window);
  if ((len < 3) || (len > 4))
    return FALSE;
  if (! ((! window->children->is_atom)
         && (window->children->next->is_atom)
         && (window->children->next->next->is_atom)))
    return FALSE;
  if ((len == 4)
      && (! window->children->next->next->next->is_atom))
    return FALSE;

  /* check the diff. ### currently we support only svndiff version
     0 delta data. */
  diff = window->children;
  if ((svn_skel__list_length(diff) == 3)
      && (svn_skel__matches_atom(diff->children, "svndiff"))
      && ((svn_skel__matches_atom(diff->children->next, "0"))
          || (svn_skel__matches_atom(diff->children->next, "1")))
      && (diff->children->next->next->is_atom))
    return TRUE;

  return FALSE;
}