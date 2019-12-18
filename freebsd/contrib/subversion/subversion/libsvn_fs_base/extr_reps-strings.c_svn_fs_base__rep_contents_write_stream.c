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
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct rep_write_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  rep_contents_clear (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rep_write_close_contents ; 
 int /*<<< orphan*/  rep_write_contents ; 
 struct rep_write_baton* rep_write_get_baton (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct rep_write_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_base__rep_contents_write_stream(svn_stream_t **ws_p,
                                       svn_fs_t *fs,
                                       const char *rep_key,
                                       const char *txn_id,
                                       svn_boolean_t use_trail_for_writes,
                                       trail_t *trail,
                                       apr_pool_t *pool)
{
  struct rep_write_baton *wb;

  /* Clear the current rep contents (free mutability check!). */
  SVN_ERR(rep_contents_clear(fs, rep_key, txn_id, trail, pool));

  /* Now, generate the write baton and stream. */
  wb = rep_write_get_baton(fs, rep_key, txn_id,
                           use_trail_for_writes ? trail : NULL, pool);
  *ws_p = svn_stream_create(wb, pool);
  svn_stream_set_write(*ws_p, rep_write_contents);
  svn_stream_set_close(*ws_p, rep_write_close_contents);

  return SVN_NO_ERROR;
}