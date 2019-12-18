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
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ head_revision; int /*<<< orphan*/  pool; int /*<<< orphan*/  root_op; int /*<<< orphan*/  ra_session; } ;
typedef  TYPE_1__ svn_client__mtcc_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_7__ {scalar_t__ src_rev; int /*<<< orphan*/  src_relpath; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ mtcc_op_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_ADD_DIR ; 
 int /*<<< orphan*/  OP_ADD_FILE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mtcc_op_find (TYPE_2__**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtcc_verify_create (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_client__mtcc_add_copy(const char *src_relpath,
                          svn_revnum_t revision,
                          const char *dst_relpath,
                          svn_client__mtcc_t *mtcc,
                          apr_pool_t *scratch_pool)
{
  mtcc_op_t *op;
  svn_boolean_t created;
  svn_node_kind_t kind;

  SVN_ERR_ASSERT(svn_relpath_is_canonical(src_relpath)
                 && svn_relpath_is_canonical(dst_relpath));

  if (! SVN_IS_VALID_REVNUM(revision))
    revision = mtcc->head_revision;
  else if (revision > mtcc->head_revision)
    {
      return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                               _("No such revision %ld"), revision);
    }

  SVN_ERR(mtcc_verify_create(mtcc, dst_relpath, scratch_pool));

  /* Subversion requires the kind of a copy */
  SVN_ERR(svn_ra_check_path(mtcc->ra_session, src_relpath, revision, &kind,
                            scratch_pool));

  if (kind != svn_node_dir && kind != svn_node_file)
    {
      return svn_error_createf(SVN_ERR_FS_NOT_FOUND, NULL,
                               _("Path '%s' not found in revision %ld"),
                               src_relpath, revision);
    }

  SVN_ERR(mtcc_op_find(&op, &created, dst_relpath, mtcc->root_op, FALSE, FALSE,
                       (kind == svn_node_file), mtcc->pool, scratch_pool));

  if (!op || !created)
    {
      return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                               _("Can't add node at '%s'"),
                               dst_relpath);
    }

  op->kind = (kind == svn_node_file) ? OP_ADD_FILE : OP_ADD_DIR;
  op->src_relpath = apr_pstrdup(mtcc->pool, src_relpath);
  op->src_rev = revision;

  return SVN_NO_ERROR;
}