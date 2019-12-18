#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_4__ {int may_check_for_error; int compression_level; int /*<<< orphan*/ * remote_ip; int /*<<< orphan*/  stream; int /*<<< orphan*/ * pool; scalar_t__ zero_copy_limit; int /*<<< orphan*/  capabilities; int /*<<< orphan*/ * block_baton; int /*<<< orphan*/ * block_handler; scalar_t__ current_out; void* max_out; scalar_t__ current_in; void* max_in; scalar_t__ error_check_interval; scalar_t__ written_since_error_check; scalar_t__ write_pos; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_end; int /*<<< orphan*/  read_ptr; int /*<<< orphan*/ * session; int /*<<< orphan*/  encrypted; int /*<<< orphan*/ * sock; } ;
typedef  TYPE_1__ svn_ra_svn_conn_t ;
typedef  int /*<<< orphan*/  apr_uintptr_t ;
typedef  void* apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_socket_t ;
typedef  int /*<<< orphan*/  apr_sockaddr_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_ALIGN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  APR_REMOTE ; 
 scalar_t__ APR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SVN_RA_SVN__PAGE_SIZE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 void* apr_palloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ apr_sockaddr_ip_get (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_socket_addr_get (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_ra_svn__stream_from_sock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__stream_from_streams (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__stream_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

svn_ra_svn_conn_t *svn_ra_svn_create_conn5(apr_socket_t *sock,
                                           svn_stream_t *in_stream,
                                           svn_stream_t *out_stream,
                                           int compression_level,
                                           apr_size_t zero_copy_limit,
                                           apr_size_t error_check_interval,
                                           apr_uint64_t max_in,
                                           apr_uint64_t max_out,
                                           apr_pool_t *result_pool)
{
  svn_ra_svn_conn_t *conn;
  void *mem = apr_palloc(result_pool, sizeof(*conn) + SVN_RA_SVN__PAGE_SIZE);
  conn = (void*)APR_ALIGN((apr_uintptr_t)mem, SVN_RA_SVN__PAGE_SIZE);

  assert((sock && !in_stream && !out_stream)
         || (!sock && in_stream && out_stream));
#ifdef SVN_HAVE_SASL
  conn->sock = sock;
  conn->encrypted = FALSE;
#endif
  conn->session = NULL;
  conn->read_ptr = conn->read_buf;
  conn->read_end = conn->read_buf;
  conn->write_pos = 0;
  conn->written_since_error_check = 0;
  conn->error_check_interval = error_check_interval;
  conn->may_check_for_error = error_check_interval == 0;
  conn->max_in = max_in;
  conn->current_in = 0;
  conn->max_out = max_out;
  conn->current_out = 0;
  conn->block_handler = NULL;
  conn->block_baton = NULL;
  conn->capabilities = apr_hash_make(result_pool);
  conn->compression_level = compression_level;
  conn->zero_copy_limit = zero_copy_limit;
  conn->pool = result_pool;

  if (sock != NULL)
    {
      apr_sockaddr_t *sa;
      conn->stream = svn_ra_svn__stream_from_sock(sock, result_pool);
      if (!(apr_socket_addr_get(&sa, APR_REMOTE, sock) == APR_SUCCESS
            && apr_sockaddr_ip_get(&conn->remote_ip, sa) == APR_SUCCESS))
        conn->remote_ip = NULL;
      svn_ra_svn__stream_timeout(conn->stream, get_timeout(conn));
    }
  else
    {
      conn->stream = svn_ra_svn__stream_from_streams(in_stream, out_stream,
                                                     result_pool);
      conn->remote_ip = NULL;
    }

  return conn;
}