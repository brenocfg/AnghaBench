#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_6__ {int mergeinfo_count; int /*<<< orphan*/  has_mergeinfo; } ;
typedef  TYPE_1__ node_revision_t ;
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_2__ dag_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_node_revision (TYPE_1__**,TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 

svn_error_t *
svn_fs_fs__dag_has_descendants_with_mergeinfo(svn_boolean_t *do_they,
                                              dag_node_t *node)
{
  node_revision_t *noderev;

  if (node->kind != svn_node_dir)
    {
      *do_they = FALSE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(get_node_revision(&noderev, node));
  if (noderev->mergeinfo_count > 1)
    *do_they = TRUE;
  else if (noderev->mergeinfo_count == 1 && !noderev->has_mergeinfo)
    *do_they = TRUE;
  else
    *do_they = FALSE;
  return SVN_NO_ERROR;
}