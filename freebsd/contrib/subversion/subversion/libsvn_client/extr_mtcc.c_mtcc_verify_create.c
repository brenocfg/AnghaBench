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
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  root_op; } ;
typedef  TYPE_1__ svn_client__mtcc_t ;
typedef  int /*<<< orphan*/  mtcc_op_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MTCC_UNMODIFIED (TYPE_1__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_ALREADY_EXISTS ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  mtcc_op_find (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__mtcc_check_path (scalar_t__*,char const*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_none ; 

__attribute__((used)) static svn_error_t *
mtcc_verify_create(svn_client__mtcc_t *mtcc,
                   const char *new_relpath,
                   apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;

  if (*new_relpath || !MTCC_UNMODIFIED(mtcc))
    {
      mtcc_op_t *op;

      SVN_ERR(mtcc_op_find(&op, NULL, new_relpath, mtcc->root_op, TRUE, FALSE,
                           FALSE, mtcc->pool, scratch_pool));

      if (op)
        return svn_error_createf(SVN_ERR_FS_ALREADY_EXISTS, NULL,
                                 _("Path '%s' already exists"),
                                 new_relpath);

      SVN_ERR(mtcc_op_find(&op, NULL, new_relpath, mtcc->root_op, TRUE, TRUE,
                           FALSE, mtcc->pool, scratch_pool));

      if (op)
        return SVN_NO_ERROR; /* Node is explicitly deleted. We can replace */
    }

  /* mod_dav_svn used to allow overwriting existing directories. Let's hide
     that for users of this api */
  SVN_ERR(svn_client__mtcc_check_path(&kind, new_relpath, FALSE,
                                      mtcc, scratch_pool));

  if (kind != svn_node_none)
    return svn_error_createf(SVN_ERR_FS_ALREADY_EXISTS, NULL,
                             _("Path '%s' already exists"),
                             new_relpath);

  return SVN_NO_ERROR;
}