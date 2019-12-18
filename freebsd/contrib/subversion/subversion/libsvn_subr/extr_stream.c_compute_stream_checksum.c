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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_kind_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN__STREAM_CHUNK_SIZE ; 
 char* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_final (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  svn_stream_read_full (int /*<<< orphan*/ *,char*,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *
compute_stream_checksum(svn_checksum_t **checksum,
                        svn_stream_t *stream,
                        svn_checksum_kind_t kind,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_checksum_ctx_t *ctx = svn_checksum_ctx_create(kind, scratch_pool);
  char *buf = apr_palloc(scratch_pool, SVN__STREAM_CHUNK_SIZE);

  while (1)
    {
      apr_size_t len = SVN__STREAM_CHUNK_SIZE;

      SVN_ERR(svn_stream_read_full(stream, buf, &len));

      if (len > 0)
        SVN_ERR(svn_checksum_update(ctx, buf, len));

      if (len != SVN__STREAM_CHUNK_SIZE)
          break;
    }
  SVN_ERR(svn_checksum_final(checksum, ctx, result_pool));

  return SVN_NO_ERROR;
}