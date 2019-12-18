#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_svn_conn_t ;
struct TYPE_12__ {int /*<<< orphan*/ * conn; } ;
typedef  TYPE_3__ svn_ra_svn__session_baton_t ;
typedef  int /*<<< orphan*/  svn_ra_svn__list_t ;
struct TYPE_10__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__ string; } ;
struct TYPE_13__ {scalar_t__ kind; TYPE_2__ u; } ;
typedef  TYPE_4__ svn_ra_svn__item_t ;
struct TYPE_14__ {TYPE_3__* priv; } ;
typedef  TYPE_5__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_SVN_MALFORMED_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SVN_STRING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  handle_auth_request (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* reparent_path (TYPE_5__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_final (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/ * svn_checksum_mismatch_err (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_checksum_parse_hex (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_svn__parse_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_ra_svn__read_cmd_response (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  svn_ra_svn__read_item (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  svn_ra_svn__write_cmd_get_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static svn_error_t *ra_svn_get_file(svn_ra_session_t *session, const char *path,
                                    svn_revnum_t rev, svn_stream_t *stream,
                                    svn_revnum_t *fetched_rev,
                                    apr_hash_t **props,
                                    apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess_baton = session->priv;
  svn_ra_svn_conn_t *conn = sess_baton->conn;
  svn_ra_svn__list_t *proplist;
  const char *expected_digest;
  svn_checksum_t *expected_checksum = NULL;
  svn_checksum_ctx_t *checksum_ctx;
  apr_pool_t *iterpool;

  path = reparent_path(session, path, pool);
  SVN_ERR(svn_ra_svn__write_cmd_get_file(conn, pool, path, rev,
                                         (props != NULL), (stream != NULL)));
  SVN_ERR(handle_auth_request(sess_baton, pool));
  SVN_ERR(svn_ra_svn__read_cmd_response(conn, pool, "(?c)rl",
                                        &expected_digest,
                                        &rev, &proplist));

  if (fetched_rev)
    *fetched_rev = rev;
  if (props)
    SVN_ERR(svn_ra_svn__parse_proplist(proplist, pool, props));

  /* We're done if the contents weren't wanted. */
  if (!stream)
    return SVN_NO_ERROR;

  if (expected_digest)
    {
      SVN_ERR(svn_checksum_parse_hex(&expected_checksum, svn_checksum_md5,
                                     expected_digest, pool));
      checksum_ctx = svn_checksum_ctx_create(svn_checksum_md5, pool);
    }

  /* Read the file's contents. */
  iterpool = svn_pool_create(pool);
  while (1)
    {
      svn_ra_svn__item_t *item;

      svn_pool_clear(iterpool);
      SVN_ERR(svn_ra_svn__read_item(conn, iterpool, &item));
      if (item->kind != SVN_RA_SVN_STRING)
        return svn_error_create(SVN_ERR_RA_SVN_MALFORMED_DATA, NULL,
                                _("Non-string as part of file contents"));
      if (item->u.string.len == 0)
        break;

      if (expected_checksum)
        SVN_ERR(svn_checksum_update(checksum_ctx, item->u.string.data,
                                    item->u.string.len));

      SVN_ERR(svn_stream_write(stream, item->u.string.data,
                               &item->u.string.len));
    }
  svn_pool_destroy(iterpool);

  SVN_ERR(svn_ra_svn__read_cmd_response(conn, pool, ""));

  if (expected_checksum)
    {
      svn_checksum_t *checksum;

      SVN_ERR(svn_checksum_final(&checksum, checksum_ctx, pool));
      if (!svn_checksum_match(checksum, expected_checksum))
        return svn_checksum_mismatch_err(expected_checksum, checksum, pool,
                                         _("Checksum mismatch for '%s'"),
                                         path);
    }

  return SVN_NO_ERROR;
}