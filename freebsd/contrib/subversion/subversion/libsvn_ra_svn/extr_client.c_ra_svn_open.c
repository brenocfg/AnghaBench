#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_svn__session_baton_t ;
struct TYPE_9__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_10__ {int /*<<< orphan*/  tunnel_baton; int /*<<< orphan*/  (* check_tunnel_func ) (int /*<<< orphan*/ ,char const*) ;scalar_t__ open_tunnel_func; } ;
typedef  TYPE_2__ svn_ra_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  svn_auth_baton_t ;
struct TYPE_11__ {int /*<<< orphan*/  hostinfo; } ;
typedef  TYPE_3__ apr_uri_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_AUTH_PARAM_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_AUTH_PARAM_CONFIG_CATEGORY_SERVERS ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_CONFIG ; 
 int /*<<< orphan*/  SVN_CONFIG_CATEGORY_SERVERS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_BAD_URL ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  find_tunnel_agent (char const*,char const*,char const***,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_hostinfo (char const*) ; 
 int /*<<< orphan*/  open_session (int /*<<< orphan*/ **,char const*,TYPE_3__*,char const*,char const**,int /*<<< orphan*/ *,TYPE_2__ const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_tunnel (char const*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_url (char const*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_auth_set_parameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_path_uri_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_open(svn_ra_session_t *session,
                                const char **corrected_url,
                                const char *url,
                                const svn_ra_callbacks2_t *callbacks,
                                void *callback_baton,
                                svn_auth_baton_t *auth_baton,
                                apr_hash_t *config,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  apr_pool_t *sess_pool = svn_pool_create(result_pool);
  svn_ra_svn__session_baton_t *sess;
  const char *tunnel, **tunnel_argv;
  apr_uri_t uri;
  svn_config_t *cfg, *cfg_client;

  /* We don't support server-prescribed redirections in ra-svn. */
  if (corrected_url)
    *corrected_url = NULL;

  SVN_ERR(parse_url(url, &uri, sess_pool));

  parse_tunnel(url, &tunnel, result_pool);

  /* Use the default tunnel implementation if we got a tunnel name,
     but either do not have tunnel handler callbacks installed, or
     the handlers don't like the tunnel name. */
  if (tunnel
      && (!callbacks->open_tunnel_func
          || (callbacks->check_tunnel_func && callbacks->open_tunnel_func
              && !callbacks->check_tunnel_func(callbacks->tunnel_baton,
                                               tunnel))))
    {
      const char *decoded_hostinfo;

      decoded_hostinfo = svn_path_uri_decode(uri.hostinfo, result_pool);

      if (!is_valid_hostinfo(decoded_hostinfo))
        return svn_error_createf(SVN_ERR_BAD_URL, NULL, _("Invalid host '%s'"),
                                 uri.hostinfo);

      SVN_ERR(find_tunnel_agent(tunnel, decoded_hostinfo, &tunnel_argv,
                                config, result_pool));
    }
  else
    tunnel_argv = NULL;

  cfg_client = config
               ? svn_hash_gets(config, SVN_CONFIG_CATEGORY_CONFIG)
               : NULL;
  cfg = config ? svn_hash_gets(config, SVN_CONFIG_CATEGORY_SERVERS) : NULL;
  svn_auth_set_parameter(auth_baton,
                         SVN_AUTH_PARAM_CONFIG_CATEGORY_CONFIG, cfg_client);
  svn_auth_set_parameter(auth_baton,
                         SVN_AUTH_PARAM_CONFIG_CATEGORY_SERVERS, cfg);

  /* We open the session in a subpool so we can get rid of it if we
     reparent with a server that doesn't support reparenting. */
  SVN_ERR(open_session(&sess, url, &uri, tunnel, tunnel_argv, config,
                       callbacks, callback_baton,
                       auth_baton, sess_pool, scratch_pool));
  session->priv = sess;

  return SVN_NO_ERROR;
}