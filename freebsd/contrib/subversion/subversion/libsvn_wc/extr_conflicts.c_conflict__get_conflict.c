#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_3__* children; struct TYPE_7__* next; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {TYPE_1__* next; } ;
struct TYPE_6__ {TYPE_2__* children; int /*<<< orphan*/  is_atom; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_skel__matches_atom (TYPE_3__*,char const*) ; 

__attribute__((used)) static svn_error_t *
conflict__get_conflict(svn_skel_t **conflict,
                       const svn_skel_t *conflict_skel,
                       const char *conflict_type)
{
  svn_skel_t *c;

  SVN_ERR_ASSERT(conflict_skel
                 && conflict_skel->children
                 && conflict_skel->children->next
                 && !conflict_skel->children->next->is_atom);

  for(c = conflict_skel->children->next->children;
      c;
      c = c->next)
    {
      if (svn_skel__matches_atom(c->children, conflict_type))
        {
          *conflict = c;
          return SVN_NO_ERROR;
        }
    }

  *conflict = NULL;

  return SVN_NO_ERROR;
}