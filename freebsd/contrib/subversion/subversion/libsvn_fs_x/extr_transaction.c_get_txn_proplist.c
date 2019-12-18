#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stringbuf_t ;
typedef  scalar_t__ svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_X__INVALID_TXN_ID ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_psprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__parse_properties (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_props (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf__morph_into_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_from_file2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_txn_proplist(apr_hash_t **proplist,
                 svn_fs_t *fs,
                 svn_fs_x__txn_id_t txn_id,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_stringbuf_t *content;

  /* Check for issue #3696. (When we find and fix the cause, we can change
   * this to an assertion.) */
  if (txn_id == SVN_FS_X__INVALID_TXN_ID)
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                            _("Internal error: a null transaction id was "
                              "passed to get_txn_proplist()"));

  /* Open the transaction properties file. */
  SVN_ERR(svn_stringbuf_from_file2(&content,
                                   svn_fs_x__path_txn_props(fs, txn_id,
                                                            scratch_pool),
                                   result_pool));

  /* Read in the property list. */
  SVN_ERR_W(svn_fs_x__parse_properties(proplist,
                                   svn_stringbuf__morph_into_string(content),
                                   result_pool),
            apr_psprintf(scratch_pool,
                         _("malformed property list in transaction '%s'"),
                         svn_fs_x__path_txn_props(fs, txn_id, scratch_pool)));

  return SVN_NO_ERROR;
}