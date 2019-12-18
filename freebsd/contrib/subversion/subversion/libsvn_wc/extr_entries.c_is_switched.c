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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_4__ {scalar_t__ repos_id; scalar_t__ repos_relpath; int /*<<< orphan*/  local_relpath; } ;
typedef  TYPE_1__ db_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  svn_relpath_basename (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_boolean_t
is_switched(db_node_t *parent,
            db_node_t *child,
            apr_pool_t *scratch_pool)
{
  if (parent && child)
    {
      if (parent->repos_id != child->repos_id)
        return TRUE;

      if (parent->repos_relpath && child->repos_relpath)
        {
          const char *unswitched
            = svn_relpath_join(parent->repos_relpath,
                               svn_relpath_basename(child->local_relpath,
                                                    scratch_pool),
                               scratch_pool);
          if (strcmp(unswitched, child->repos_relpath))
            return TRUE;
        }
    }

  return FALSE;
}