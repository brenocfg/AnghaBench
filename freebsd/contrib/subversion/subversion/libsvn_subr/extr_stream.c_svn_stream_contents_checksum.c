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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * compute_stream_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 

svn_error_t *
svn_stream_contents_checksum(svn_checksum_t **checksum,
                             svn_stream_t *stream,
                             svn_checksum_kind_t kind,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  svn_error_t *err;

  err = compute_stream_checksum(checksum, stream, kind,
                                result_pool, scratch_pool);

  /* Close source stream in all cases. */
  return svn_error_compose_create(err, svn_stream_close(stream));
}