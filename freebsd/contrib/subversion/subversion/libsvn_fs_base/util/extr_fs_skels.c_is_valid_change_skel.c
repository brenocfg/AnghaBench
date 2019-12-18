#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* next; struct TYPE_9__* children; scalar_t__ is_atom; } ;
typedef  TYPE_3__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change_kind_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_8__ {TYPE_1__* next; scalar_t__ is_atom; } ;
struct TYPE_7__ {TYPE_3__* next; scalar_t__ is_atom; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_path_change_add ; 
 int /*<<< orphan*/  svn_fs_path_change_delete ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 
 int /*<<< orphan*/  svn_fs_path_change_replace ; 
 int /*<<< orphan*/  svn_fs_path_change_reset ; 
 int svn_skel__list_length (TYPE_3__*) ; 
 scalar_t__ svn_skel__matches_atom (TYPE_3__*,char*) ; 

__attribute__((used)) static svn_boolean_t
is_valid_change_skel(svn_skel_t *skel, svn_fs_path_change_kind_t *kind)
{
  if ((svn_skel__list_length(skel) == 6)
      && svn_skel__matches_atom(skel->children, "change")
      && skel->children->next->is_atom
      && skel->children->next->next->is_atom
      && skel->children->next->next->next->is_atom
      && skel->children->next->next->next->next->is_atom
      && skel->children->next->next->next->next->next->is_atom)
    {
      svn_skel_t *kind_skel = skel->children->next->next->next;

      /* check the kind (and return it) */
      if (svn_skel__matches_atom(kind_skel, "reset"))
        {
          if (kind)
            *kind = svn_fs_path_change_reset;
          return TRUE;
        }
      if (svn_skel__matches_atom(kind_skel, "add"))
        {
          if (kind)
            *kind = svn_fs_path_change_add;
          return TRUE;
        }
      if (svn_skel__matches_atom(kind_skel, "delete"))
        {
          if (kind)
            *kind = svn_fs_path_change_delete;
          return TRUE;
        }
      if (svn_skel__matches_atom(kind_skel, "replace"))
        {
          if (kind)
            *kind = svn_fs_path_change_replace;
          return TRUE;
        }
      if (svn_skel__matches_atom(kind_skel, "modify"))
        {
          if (kind)
            *kind = svn_fs_path_change_modify;
          return TRUE;
        }
    }
  return FALSE;
}