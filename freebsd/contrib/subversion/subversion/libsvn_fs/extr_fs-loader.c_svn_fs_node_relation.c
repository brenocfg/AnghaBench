#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ fs; TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* node_relation ) (int /*<<< orphan*/ *,TYPE_2__*,char const*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,char const*,TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_node_unrelated ; 

svn_error_t *
svn_fs_node_relation(svn_fs_node_relation_t *relation,
                     svn_fs_root_t *root_a, const char *path_a,
                     svn_fs_root_t *root_b, const char *path_b,
                     apr_pool_t *scratch_pool)
{
  /* Different repository types? */
  if (root_a->fs != root_b->fs)
    {
      *relation = svn_fs_node_unrelated;
      return SVN_NO_ERROR;
    }

  return svn_error_trace(root_a->vtable->node_relation(relation,
                                                       root_a, path_a,
                                                       root_b, path_b,
                                                       scratch_pool));
}