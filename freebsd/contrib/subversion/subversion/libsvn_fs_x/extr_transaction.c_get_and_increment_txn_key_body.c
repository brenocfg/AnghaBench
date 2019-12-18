#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ txn_number; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ get_and_increment_txn_key_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 scalar_t__ svn__base36toui64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn__ui64tobase36 (char*,scalar_t__) ; 
 char* svn_fs_x__path_txn_current (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_fs_x__path_txn_dir (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__read_content (TYPE_1__**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_write_atomic2 (char const*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_and_increment_txn_key_body(void *baton,
                               apr_pool_t *scratch_pool)
{
  get_and_increment_txn_key_baton_t *cb = baton;
  svn_fs_t *fs = cb->fs;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  const char *txn_current_path = svn_fs_x__path_txn_current(fs, scratch_pool);
  char new_id_str[SVN_INT64_BUFFER_SIZE];

  svn_stringbuf_t *buf;
  SVN_ERR(svn_fs_x__read_content(&buf, txn_current_path, scratch_pool));

  /* Parse the txn number, stopping at the next non-digit.
   *
   * Note that an empty string is being interpreted as "0".
   * This gives us implicit recovery if the file contents should be lost
   * due to e.g. power failure.
   */
  cb->txn_number = svn__base36toui64(NULL, buf->data);
  if (cb->txn_number == 0)
    ++cb->txn_number;

  /* Check for conflicts.  Those might happen if the server crashed and we
   * had 'svnadmin recover' reset the txn counter.
   *
   * Once we found an unused txn id, claim it by creating the respective
   * txn directory.
   *
   * Note that this is not racy because we hold the txn-current-lock.
   */
  while (TRUE)
    {
      const char *txn_dir;
      svn_node_kind_t kind;
      svn_pool_clear(iterpool);

      txn_dir = svn_fs_x__path_txn_dir(fs, cb->txn_number, iterpool);
      SVN_ERR(svn_io_check_path(txn_dir, &kind, iterpool));
      if (kind == svn_node_none)
        {
          svn_io_dir_make(txn_dir, APR_OS_DEFAULT, iterpool);
          break;
        }

      ++cb->txn_number;
    }

  /* Increment the key and add a trailing \n to the string so the
     txn-current file has a newline in it. */
  SVN_ERR(svn_io_write_atomic2(txn_current_path, new_id_str,
                               svn__ui64tobase36(new_id_str,
                                                 cb->txn_number + 1),
                               txn_current_path, FALSE, scratch_pool));

  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}