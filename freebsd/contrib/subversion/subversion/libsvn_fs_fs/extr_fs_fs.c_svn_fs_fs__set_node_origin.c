#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
struct TYPE_7__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_EACCES (int /*<<< orphan*/ ) ; 
 TYPE_1__* set_node_origins_for_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_fs__id_unparse (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_node_origin (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__set_node_origin(svn_fs_t *fs,
                           const svn_fs_fs__id_part_t *node_id,
                           const svn_fs_id_t *node_rev_id,
                           apr_pool_t *pool)
{
  svn_error_t *err;
  const char *filename = svn_fs_fs__path_node_origin(fs, node_id, pool);

  err = set_node_origins_for_file(fs, filename,
                                  node_id,
                                  svn_fs_fs__id_unparse(node_rev_id, pool),
                                  pool);
  if (err && APR_STATUS_IS_EACCES(err->apr_err))
    {
      /* It's just a cache; stop trying if I can't write. */
      svn_error_clear(err);
      err = NULL;
    }
  return svn_error_trace(err);
}