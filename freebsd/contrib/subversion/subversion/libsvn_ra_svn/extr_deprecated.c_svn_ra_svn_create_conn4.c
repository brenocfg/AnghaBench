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
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_ra_svn_create_conn5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_ra_svn_conn_t *
svn_ra_svn_create_conn4(apr_socket_t *sock,
                        svn_stream_t *in_stream,
                        svn_stream_t *out_stream,
                        int compression_level,
                        apr_size_t zero_copy_limit,
                        apr_size_t error_check_interval,
                        apr_pool_t *pool)
{
  return svn_ra_svn_create_conn5(sock, in_stream, out_stream,
                                 compression_level, zero_copy_limit,
                                 error_check_interval, 0, 0, pool);
}