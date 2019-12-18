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
struct TYPE_5__ {scalar_t__ fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_fs_node_relation_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  base_node_id (int /*<<< orphan*/  const**,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__id_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_fs_node_unrelated ; 

__attribute__((used)) static svn_error_t *
base_node_relation(svn_fs_node_relation_t *relation,
                   svn_fs_root_t *root_a, const char *path_a,
                   svn_fs_root_t *root_b, const char *path_b,
                   apr_pool_t *pool)
{
  const svn_fs_id_t *id_a, *id_b;

  /* Paths from different repository are never related. */
  if (root_a->fs != root_b->fs)
    {
      *relation = svn_fs_node_unrelated;
      return SVN_NO_ERROR;
    }

  /* Naive implementation. */
  SVN_ERR(base_node_id(&id_a, root_a, path_a, pool));
  SVN_ERR(base_node_id(&id_b, root_b, path_b, pool));

  *relation = svn_fs_base__id_compare(id_a, id_b);

  return SVN_NO_ERROR;
}