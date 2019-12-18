#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; TYPE_2__* root_op; } ;
typedef  TYPE_1__ svn_client__mtcc_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/ * prop_mods; int /*<<< orphan*/ * children; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ mtcc_op_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ MTCC_UNMODIFIED (TYPE_1__*) ; 
 int /*<<< orphan*/  OP_DELETE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_PATH_IS_EMPTY (char const*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ mtcc_op_contains_non_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  mtcc_op_find (TYPE_2__**,scalar_t__*,char const*,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client__mtcc_check_path (scalar_t__*,char const*,scalar_t__,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_relpath_is_canonical (char const*) ; 

__attribute__((used)) static svn_error_t *
mtcc_add_delete(const char *relpath,
                svn_boolean_t for_move,
                svn_client__mtcc_t *mtcc,                
                apr_pool_t *scratch_pool)
{
  mtcc_op_t *op;
  svn_boolean_t created;
  svn_node_kind_t kind;

  SVN_ERR_ASSERT(svn_relpath_is_canonical(relpath));

  SVN_ERR(svn_client__mtcc_check_path(&kind, relpath, FALSE,
                                      mtcc, scratch_pool));

  if (kind == svn_node_none)
    return svn_error_createf(SVN_ERR_FS_NOT_FOUND, NULL,
                             _("Can't delete node at '%s' as it "
                                "does not exist"),
                             relpath);

  if (SVN_PATH_IS_EMPTY(relpath) && MTCC_UNMODIFIED(mtcc))
    {
      /* Turn root operation into delete */
      op = mtcc->root_op;
    }
  else
    {
      SVN_ERR(mtcc_op_find(&op, &created, relpath, mtcc->root_op, FALSE, TRUE,
                           TRUE, mtcc->pool, scratch_pool));

      if (!for_move && !op && !created)
        {
          /* Allow deleting directories, that are unmodified except for
              one or more deleted descendants */
          
          SVN_ERR(mtcc_op_find(&op, &created, relpath, mtcc->root_op, TRUE,
                  FALSE, FALSE, mtcc->pool, scratch_pool));

          if (op && mtcc_op_contains_non_delete(op))
            op = NULL;
          else
            created = TRUE;
        }

      if (!op || !created)
        {
          return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                                   _("Can't delete node at '%s'"),
                                   relpath);
        }
    }

  op->kind = OP_DELETE;
  op->children = NULL;
  op->prop_mods = NULL;

  return SVN_NO_ERROR;
}