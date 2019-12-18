#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_txdelta_stream_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_3__ {int /*<<< orphan*/  session; int /*<<< orphan*/  open_baton; int /*<<< orphan*/  (* open_func ) (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ open_txdelta_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  negotiate_put_encoding (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__create_stream_bucket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_txdelta_to_svndiff_stream (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txdelta_stream_errfunc ; 

__attribute__((used)) static svn_error_t *
create_body_from_txdelta_stream(serf_bucket_t **body_bkt,
                                void *baton,
                                serf_bucket_alloc_t *alloc,
                                apr_pool_t *pool /* request pool */,
                                apr_pool_t *scratch_pool)
{
  open_txdelta_baton_t *b = baton;
  svn_txdelta_stream_t *txdelta_stream;
  svn_stream_t *stream;
  int svndiff_version;
  int compression_level;

  SVN_ERR(b->open_func(&txdelta_stream, b->open_baton, pool, scratch_pool));

  negotiate_put_encoding(&svndiff_version, &compression_level, b->session);
  stream = svn_txdelta_to_svndiff_stream(txdelta_stream, svndiff_version,
                                         compression_level, pool);
  *body_bkt = svn_ra_serf__create_stream_bucket(stream, alloc,
                                                txdelta_stream_errfunc, b);

  return SVN_NO_ERROR;
}