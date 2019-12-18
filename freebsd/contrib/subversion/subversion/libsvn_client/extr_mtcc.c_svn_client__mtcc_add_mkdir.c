#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  pool; TYPE_6__* root_op; } ;
typedef  TYPE_1__ svn_client__mtcc_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_9__ {void* kind; } ;
typedef  TYPE_2__ mtcc_op_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {void* kind; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MTCC_UNMODIFIED (TYPE_1__*) ; 
 void* OP_ADD_DIR ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  mtcc_op_find (TYPE_2__**,int /*<<< orphan*/ *,char const*,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtcc_verify_create (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

svn_error_t *
svn_client__mtcc_add_mkdir(const char *relpath,
                           svn_client__mtcc_t *mtcc,
                           apr_pool_t *scratch_pool)
{
  mtcc_op_t *op;
  svn_boolean_t created;
  SVN_ERR_ASSERT(svn_relpath_is_canonical(relpath));

  SVN_ERR(mtcc_verify_create(mtcc, relpath, scratch_pool));

  if (SVN_PATH_IS_EMPTY(relpath) && MTCC_UNMODIFIED(mtcc))
    {
      /* Turn the root of the operation in an MKDIR */
      mtcc->root_op->kind = OP_ADD_DIR;

      return SVN_NO_ERROR;
    }

  SVN_ERR(mtcc_op_find(&op, &created, relpath, mtcc->root_op, FALSE, FALSE,
                       FALSE, mtcc->pool, scratch_pool));

  if (!op || !created)
    {
      return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                               _("Can't create directory at '%s'"),
                               relpath);
    }

  op->kind = OP_ADD_DIR;

  return SVN_NO_ERROR;
}