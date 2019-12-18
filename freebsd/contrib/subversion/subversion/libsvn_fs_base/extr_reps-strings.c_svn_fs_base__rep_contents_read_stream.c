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
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct rep_read_baton {int dummy; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  rep_read_contents ; 
 int /*<<< orphan*/  rep_read_get_baton (struct rep_read_baton**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (struct rep_read_baton*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_base__rep_contents_read_stream(svn_stream_t **rs_p,
                                      svn_fs_t *fs,
                                      const char *rep_key,
                                      svn_boolean_t use_trail_for_reads,
                                      trail_t *trail,
                                      apr_pool_t *pool)
{
  struct rep_read_baton *rb;

  SVN_ERR(rep_read_get_baton(&rb, fs, rep_key, use_trail_for_reads,
                             trail, pool));
  *rs_p = svn_stream_create(rb, pool);
  svn_stream_set_read2(*rs_p, NULL /* only full read support */,
                       rep_read_contents);

  return SVN_NO_ERROR;
}