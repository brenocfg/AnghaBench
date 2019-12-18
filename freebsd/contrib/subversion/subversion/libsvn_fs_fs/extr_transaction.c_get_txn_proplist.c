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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCORRECT_PARAMS ; 
 int /*<<< orphan*/  SVN_HASH_TERMINATOR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  path_txn_props (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_quick_wrapf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__id_txn_used (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * svn_hash_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_open_readonly (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_txn_proplist(apr_hash_t *proplist,
                 svn_fs_t *fs,
                 const svn_fs_fs__id_part_t *txn_id,
                 apr_pool_t *pool)
{
  svn_stream_t *stream;
  svn_error_t *err;

  /* Check for issue #3696. (When we find and fix the cause, we can change
   * this to an assertion.) */
  if (!txn_id || !svn_fs_fs__id_txn_used(txn_id))
    return svn_error_create(SVN_ERR_INCORRECT_PARAMS, NULL,
                            _("Internal error: a null transaction id was "
                              "passed to get_txn_proplist()"));

  /* Open the transaction properties file. */
  SVN_ERR(svn_stream_open_readonly(&stream, path_txn_props(fs, txn_id, pool),
                                   pool, pool));

  /* Read in the property list. */
  err = svn_hash_read2(proplist, stream, SVN_HASH_TERMINATOR, pool);
  if (err)
    {
      err = svn_error_compose_create(err, svn_stream_close(stream));
      return svn_error_quick_wrapf(err,
               _("malformed property list in transaction '%s'"),
               path_txn_props(fs, txn_id, pool));
    }

  return svn_stream_close(stream);
}