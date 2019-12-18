#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  pool; int /*<<< orphan*/ * sock; } ;
typedef  TYPE_1__ sock_baton_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sock_pending_cb ; 
 int /*<<< orphan*/  sock_read_cb ; 
 int /*<<< orphan*/  sock_timeout_cb ; 
 int /*<<< orphan*/  sock_write_cb ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_svn__stream_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_data_available (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_ra_svn__stream_t *
svn_ra_svn__stream_from_sock(apr_socket_t *sock,
                             apr_pool_t *result_pool)
{
  sock_baton_t *b = apr_palloc(result_pool, sizeof(*b));
  svn_stream_t *sock_stream;

  b->sock = sock;
  b->pool = svn_pool_create(result_pool);

  sock_stream = svn_stream_create(b, result_pool);

  svn_stream_set_read2(sock_stream, sock_read_cb, NULL /* use default */);
  svn_stream_set_write(sock_stream, sock_write_cb);
  svn_stream_set_data_available(sock_stream, sock_pending_cb);

  return svn_ra_svn__stream_create(sock_stream, sock_stream,
                                   b, sock_timeout_cb, result_pool);
}