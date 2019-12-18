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
typedef  int /*<<< orphan*/  svn_fs_x__change_t ;
typedef  int /*<<< orphan*/  (* svn_fs_x__change_receiver_t ) (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_change (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__read_changes_incrementally(svn_stream_t *stream,
                                     svn_fs_x__change_receiver_t
                                       change_receiver,
                                     void *change_receiver_baton,
                                     apr_pool_t *scratch_pool)
{
  svn_fs_x__change_t *change;
  apr_pool_t *iterpool;

  iterpool = svn_pool_create(scratch_pool);
  do
    {
      svn_pool_clear(iterpool);

      SVN_ERR(read_change(&change, stream, iterpool, iterpool));
      if (change)
        SVN_ERR(change_receiver(change_receiver_baton, change, iterpool));
    }
  while (change);
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}