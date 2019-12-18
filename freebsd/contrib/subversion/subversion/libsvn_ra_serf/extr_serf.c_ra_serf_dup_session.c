#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_13__ {char const* useragent; char const* vcc_url; char const* activity_collection_url; char const* proxy_username; char const* proxy_password; char const* ssl_authorities; char const* uuid; char const* me_resource; char const* rev_stub; char const* txn_stub; char const* txn_root_stub; char const* vtxn_stub; char const* vtxn_root_stub; char const* server_allows_bulk; char const* repos_root_str; char const* session_url_str; int num_conns; scalar_t__ cur_conn; int /*<<< orphan*/  context; TYPE_4__** conns; int /*<<< orphan*/  session_url; scalar_t__ config; int /*<<< orphan*/  repos_root; int /*<<< orphan*/ * pool; int /*<<< orphan*/  blncache; void* supported_posts; scalar_t__ proxy_auth_attempts; void* capabilities; int /*<<< orphan*/ * pending_error; scalar_t__ auth_attempts; int /*<<< orphan*/ * auth_state; } ;
typedef  TYPE_2__ svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {int last_status_code; int /*<<< orphan*/  conn; TYPE_2__* session; int /*<<< orphan*/  bkt_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* apr_hash_copy (int /*<<< orphan*/ *,void*) ; 
 TYPE_4__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  load_config (TYPE_2__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_bucket_allocator_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ serf_connection_create2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_context_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_context_set_progress_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_config_copy_config (scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__blncache_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__conn_closed ; 
 int /*<<< orphan*/  svn_ra_serf__conn_setup ; 
 int /*<<< orphan*/  svn_ra_serf__progress ; 
 int /*<<< orphan*/  svn_ra_serf__uri_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_serf__wrap_err (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ra_serf_dup_session(svn_ra_session_t *new_session,
                    svn_ra_session_t *old_session,
                    const char *new_session_url,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  svn_ra_serf__session_t *old_sess = old_session->priv;
  svn_ra_serf__session_t *new_sess;
  apr_status_t status;

  new_sess = apr_pmemdup(result_pool, old_sess, sizeof(*new_sess));

  new_sess->pool = result_pool;

  if (new_sess->config)
    SVN_ERR(svn_config_copy_config(&new_sess->config, new_sess->config,
                                   result_pool));

  /* max_connections */
  /* using_ssl */
  /* using_compression */
  /* http10 */
  /* http20 */
  /* using_chunked_requests */
  /* detect_chunking */

  if (new_sess->useragent)
    new_sess->useragent = apr_pstrdup(result_pool, new_sess->useragent);

  if (new_sess->vcc_url)
    new_sess->vcc_url = apr_pstrdup(result_pool, new_sess->vcc_url);

  new_sess->auth_state = NULL;
  new_sess->auth_attempts = 0;

  /* Callback functions to get info from WC */
  /* wc_callbacks */
  /* wc_callback_baton */

  /* progress_func */
  /* progress_baton */

  /* cancel_func */
  /* cancel_baton */

  /* shim_callbacks */

  new_sess->pending_error = NULL;

  /* authn_types */

  /* Keys and values are static */
  if (new_sess->capabilities)
    new_sess->capabilities = apr_hash_copy(result_pool, new_sess->capabilities);

  if (new_sess->activity_collection_url)
    {
      new_sess->activity_collection_url
                = apr_pstrdup(result_pool, new_sess->activity_collection_url);
    }

   /* using_proxy */

  if (new_sess->proxy_username)
    {
      new_sess->proxy_username
                = apr_pstrdup(result_pool, new_sess->proxy_username);
    }

  if (new_sess->proxy_password)
    {
      new_sess->proxy_password
                = apr_pstrdup(result_pool, new_sess->proxy_password);
    }

  new_sess->proxy_auth_attempts = 0;

  /* trust_default_ca */

  if (new_sess->ssl_authorities)
    {
      new_sess->ssl_authorities = apr_pstrdup(result_pool,
                                              new_sess->ssl_authorities);
    }

  if (new_sess->uuid)
    new_sess->uuid = apr_pstrdup(result_pool, new_sess->uuid);

  /* timeout */
  /* supports_deadprop_count */

  if (new_sess->me_resource)
    new_sess->me_resource = apr_pstrdup(result_pool, new_sess->me_resource);
  if (new_sess->rev_stub)
    new_sess->rev_stub = apr_pstrdup(result_pool, new_sess->rev_stub);
  if (new_sess->txn_stub)
    new_sess->txn_stub = apr_pstrdup(result_pool, new_sess->txn_stub);
  if (new_sess->txn_root_stub)
    new_sess->txn_root_stub = apr_pstrdup(result_pool,
                                          new_sess->txn_root_stub);
  if (new_sess->vtxn_stub)
    new_sess->vtxn_stub = apr_pstrdup(result_pool, new_sess->vtxn_stub);
  if (new_sess->vtxn_root_stub)
    new_sess->vtxn_root_stub = apr_pstrdup(result_pool,
                                           new_sess->vtxn_root_stub);

  /* Keys and values are static */
  if (new_sess->supported_posts)
    new_sess->supported_posts = apr_hash_copy(result_pool,
                                              new_sess->supported_posts);

  /* ### Can we copy this? */
  SVN_ERR(svn_ra_serf__blncache_create(&new_sess->blncache,
                                       new_sess->pool));

  if (new_sess->server_allows_bulk)
    new_sess->server_allows_bulk = apr_pstrdup(result_pool,
                                               new_sess->server_allows_bulk);

  if (new_sess->repos_root_str)
    {
      new_sess->repos_root_str = apr_pstrdup(result_pool,
                                             new_sess->repos_root_str);
      SVN_ERR(svn_ra_serf__uri_parse(&new_sess->repos_root,
                                     new_sess->repos_root_str,
                                     result_pool));
    }

  new_sess->session_url_str = apr_pstrdup(result_pool, new_session_url);

  SVN_ERR(svn_ra_serf__uri_parse(&new_sess->session_url,
                                 new_sess->session_url_str,
                                 result_pool));

  /* svn_boolean_t supports_inline_props */
  /* supports_rev_rsrc_replay */
  /* supports_svndiff1 */
  /* supports_svndiff2 */
  /* supports_put_result_checksum */
  /* conn_latency */

  new_sess->context = serf_context_create(result_pool);

  SVN_ERR(load_config(new_sess, old_sess->config,
                      result_pool, scratch_pool));

  new_sess->conns[0] = apr_pcalloc(result_pool,
                                   sizeof(*new_sess->conns[0]));
  new_sess->conns[0]->bkt_alloc =
          serf_bucket_allocator_create(result_pool, NULL, NULL);
  new_sess->conns[0]->session = new_sess;
  new_sess->conns[0]->last_status_code = -1;

  /* go ahead and tell serf about the connection. */
  status =
    serf_connection_create2(&new_sess->conns[0]->conn,
                            new_sess->context,
                            new_sess->session_url,
                            svn_ra_serf__conn_setup, new_sess->conns[0],
                            svn_ra_serf__conn_closed, new_sess->conns[0],
                            result_pool);
  if (status)
    return svn_ra_serf__wrap_err(status, NULL);

  /* Set the progress callback. */
  serf_context_set_progress_cb(new_sess->context, svn_ra_serf__progress,
                               new_sess);

  new_sess->num_conns = 1;
  new_sess->cur_conn = 0;

  new_session->priv = new_sess;

  return SVN_NO_ERROR;
}