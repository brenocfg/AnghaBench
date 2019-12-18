#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_window_handler_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  conn; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ file_revs_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_ra_svn__svndiff_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cstring (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_ra_svn__write_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__write_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_ra_svn_compression_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_create (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_txdelta_to_svndiff3 (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svndiff_close_handler ; 
 int /*<<< orphan*/  svndiff_handler ; 
 int /*<<< orphan*/  write_prop_diffs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *file_rev_handler(void *baton, const char *path,
                                     svn_revnum_t rev, apr_hash_t *rev_props,
                                     svn_boolean_t merged_revision,
                                     svn_txdelta_window_handler_t *d_handler,
                                     void **d_baton,
                                     apr_array_header_t *prop_diffs,
                                     apr_pool_t *pool)
{
  file_revs_baton_t *frb = baton;
  svn_stream_t *stream;

  SVN_ERR(svn_ra_svn__write_tuple(frb->conn, pool, "cr(!",
                                  path, rev));
  SVN_ERR(svn_ra_svn__write_proplist(frb->conn, pool, rev_props));
  SVN_ERR(svn_ra_svn__write_tuple(frb->conn, pool, "!)(!"));
  SVN_ERR(write_prop_diffs(frb->conn, pool, prop_diffs));
  SVN_ERR(svn_ra_svn__write_tuple(frb->conn, pool, "!)b", merged_revision));

  /* Store the pool for the delta stream. */
  frb->pool = pool;

  /* Prepare for the delta or just write an empty string. */
  if (d_handler)
    {
      stream = svn_stream_create(baton, pool);
      svn_stream_set_write(stream, svndiff_handler);
      svn_stream_set_close(stream, svndiff_close_handler);

      svn_txdelta_to_svndiff3(d_handler, d_baton, stream,
                              svn_ra_svn__svndiff_version(frb->conn),
                              svn_ra_svn_compression_level(frb->conn), pool);
    }
  else
    SVN_ERR(svn_ra_svn__write_cstring(frb->conn, pool, ""));

  return SVN_NO_ERROR;
}