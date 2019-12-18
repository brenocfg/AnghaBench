#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
struct TYPE_13__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_editor_t ;
struct edit_baton {int /*<<< orphan*/ * txn; scalar_t__ completed; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_FS_CONFLICT ; 
 int /*<<< orphan*/  SVN_ERR_FS_INCORRECT_EDITOR_COMPLETION ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_1__* SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* svn_editor_complete (int /*<<< orphan*/ *) ; 
 struct edit_baton* svn_editor_get_baton (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_compose_create (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_fs_abort_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_fs_commit_txn (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs__editor_commit(svn_revnum_t *revision,
                      svn_error_t **post_commit_err,
                      const char **conflict_path,
                      svn_editor_t *editor,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = svn_editor_get_baton(editor);
  const char *inner_conflict_path;
  svn_error_t *err = NULL;

  /* make sure people are using the correct sequencing.  */
  if (eb->completed)
    return svn_error_create(SVN_ERR_FS_INCORRECT_EDITOR_COMPLETION,
                            NULL, NULL);

  *revision = SVN_INVALID_REVNUM;
  *post_commit_err = NULL;
  *conflict_path = NULL;

  /* Clean up internal resources (eg. eb->root). This also allows the
     editor infrastructure to know this editor is "complete".  */
  err = svn_editor_complete(editor);
  if (err)
    {
      svn_fs_txn_t *txn = eb->txn;

      eb->txn = NULL;
      return svn_error_trace(svn_error_compose_create(
                  err,
                  svn_fs_abort_txn(txn, scratch_pool)));
    }

  /* Note: docco for svn_fs_commit_txn() states that CONFLICT_PATH will
     be allocated in the txn's pool. But it lies. Regardless, we want
     it placed into RESULT_POOL.  */

  err = svn_fs_commit_txn(&inner_conflict_path,
                          revision,
                          eb->txn,
                          scratch_pool);
  if (SVN_IS_VALID_REVNUM(*revision))
    {
      if (err)
        {
          /* Case 3. ERR is a post-commit (cleanup) error.  */

          /* Pass responsibility via POST_COMMIT_ERR.  */
          *post_commit_err = err;
          err = SVN_NO_ERROR;
        }
      /* else: Case 1.  */
    }
  else
    {
      SVN_ERR_ASSERT(err != NULL);
      if (err->apr_err == SVN_ERR_FS_CONFLICT)
        {
          /* Case 2.  */

          /* Copy this into the correct pool (see note above).  */
          *conflict_path = apr_pstrdup(result_pool, inner_conflict_path);

          /* Return success. The caller should inspect CONFLICT_PATH to
             determine this particular case.  */
          svn_error_clear(err);
          err = SVN_NO_ERROR;
        }
      /* else: Case 4.  */

      /* Abort the TXN. Nobody wants to use it.  */
      /* ### should we examine the error and attempt svn_fs_purge_txn() ?  */
      err = svn_error_compose_create(
        err,
        svn_fs_abort_txn(eb->txn, scratch_pool));
    }

  /* For safety, clear the now-useless txn.  */
  eb->txn = NULL;

  return svn_error_trace(err);
}