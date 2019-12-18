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
struct TYPE_6__ {struct TYPE_6__* children; TYPE_1__* next; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  is_atom; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
conflict__get_operation(svn_skel_t **why,
                        const svn_skel_t *conflict_skel)
{
  SVN_ERR_ASSERT(conflict_skel
                 && conflict_skel->children
                 && conflict_skel->children->next
                 && !conflict_skel->children->next->is_atom);

  *why = conflict_skel->children;

  if (!(*why)->children)
    *why = NULL; /* Operation is not set yet */

  return SVN_NO_ERROR;
}