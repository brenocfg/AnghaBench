#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* conn; } ;
typedef  TYPE_2__ serf_request_t ;
struct TYPE_18__ {TYPE_1__* scheme; TYPE_6__* baton; } ;
struct TYPE_16__ {TYPE_5__ proxy_authn_info; int /*<<< orphan*/  cred_cb; } ;
typedef  TYPE_3__ serf_context_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pool; TYPE_3__* ctx; } ;
typedef  TYPE_4__ serf_connection_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  TYPE_5__ serf__authn_info_t ;
struct TYPE_19__ {char* header; int /*<<< orphan*/ * pool; void* realm; int /*<<< orphan*/  ha1; int /*<<< orphan*/  digest_nc; void* username; void* algorithm; void* opaque; int /*<<< orphan*/ * cnonce; void* nonce; void* qop; } ;
typedef  TYPE_6__ digest_authn_info_t ;
typedef  scalar_t__ apr_status_t ;
typedef  size_t apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  PROXY ; 
 scalar_t__ SERF_ERROR_AUTHN_FAILED ; 
 scalar_t__ SERF_ERROR_AUTHN_MISSING_ATTRIBUTE ; 
 int /*<<< orphan*/  apr_pool_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pool_destroy (int /*<<< orphan*/ *) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 char* apr_strtok (char*,char*,char**) ; 
 scalar_t__ build_digest_ha1 (int /*<<< orphan*/ *,char*,char*,void*,int /*<<< orphan*/ *) ; 
 char* serf__construct_realm (int /*<<< orphan*/ ,TYPE_4__*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_5__* serf__get_authn_info_for_server (TYPE_4__*) ; 
 scalar_t__ serf__provide_credentials (TYPE_3__*,char**,char**,TYPE_2__*,void*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serf_connection_set_max_outstanding_requests (TYPE_4__*,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char*) ; 

apr_status_t
serf__handle_digest_auth(int code,
                         serf_request_t *request,
                         serf_bucket_t *response,
                         const char *auth_hdr,
                         const char *auth_attr,
                         void *baton,
                         apr_pool_t *pool)
{
    char *attrs;
    char *nextkv;
    const char *realm, *realm_name = NULL;
    const char *nonce = NULL;
    const char *algorithm = NULL;
    const char *qop = NULL;
    const char *opaque = NULL;
    const char *key;
    serf_connection_t *conn = request->conn;
    serf_context_t *ctx = conn->ctx;
    serf__authn_info_t *authn_info;
    digest_authn_info_t *digest_info;
    apr_status_t status;
    apr_pool_t *cred_pool;
    char *username, *password;

    /* Can't do Digest authentication if there's no callback to get
       username & password. */
    if (!ctx->cred_cb) {
        return SERF_ERROR_AUTHN_FAILED;
    }

    if (code == 401) {
        authn_info = serf__get_authn_info_for_server(conn);
    } else {
        authn_info = &ctx->proxy_authn_info;
    }
    digest_info = authn_info->baton;

    /* Need a copy cuz we're going to write NUL characters into the string.  */
    attrs = apr_pstrdup(pool, auth_attr);

    /* We're expecting a list of key=value pairs, separated by a comma.
       Ex. realm="SVN Digest",
       nonce="f+zTl/leBAA=e371bd3070adfb47b21f5fc64ad8cc21adc371a5",
       algorithm=MD5, qop="auth" */
    for ( ; (key = apr_strtok(attrs, ",", &nextkv)) != NULL; attrs = NULL) {
        char *val;

        val = strchr(key, '=');
        if (val == NULL)
            continue;
        *val++ = '\0';

        /* skip leading spaces */
        while (*key && *key == ' ')
            key++;

        /* If the value is quoted, then remove the quotes.  */
        if (*val == '"') {
            apr_size_t last = strlen(val) - 1;

            if (val[last] == '"') {
                val[last] = '\0';
                val++;
            }
        }

        if (strcmp(key, "realm") == 0)
            realm_name = val;
        else if (strcmp(key, "nonce") == 0)
            nonce = val;
        else if (strcmp(key, "algorithm") == 0)
            algorithm = val;
        else if (strcmp(key, "qop") == 0)
            qop = val;
        else if (strcmp(key, "opaque") == 0)
            opaque = val;

        /* Ignore all unsupported attributes. */
    }

    if (!realm_name) {
        return SERF_ERROR_AUTHN_MISSING_ATTRIBUTE;
    }

    realm = serf__construct_realm(code == 401 ? HOST : PROXY,
                                  conn, realm_name,
                                  pool);

    /* Ask the application for credentials */
    apr_pool_create(&cred_pool, pool);
    status = serf__provide_credentials(ctx,
                                       &username, &password,
                                       request, baton,
                                       code, authn_info->scheme->name,
                                       realm, cred_pool);
    if (status) {
        apr_pool_destroy(cred_pool);
        return status;
    }

    digest_info->header = (code == 401) ? "Authorization" :
                                          "Proxy-Authorization";

    /* Store the digest authentication parameters in the context cached for
       this server in the serf context, so we can use it to create the
       Authorization header when setting up requests on the same or different
       connections (e.g. in case of KeepAlive off on the server).
       TODO: we currently don't cache this info per realm, so each time a request
       'switches realms', we have to ask the application for new credentials. */
    digest_info->pool = conn->pool;
    digest_info->qop = apr_pstrdup(digest_info->pool, qop);
    digest_info->nonce = apr_pstrdup(digest_info->pool, nonce);
    digest_info->cnonce = NULL;
    digest_info->opaque = apr_pstrdup(digest_info->pool, opaque);
    digest_info->algorithm = apr_pstrdup(digest_info->pool, algorithm);
    digest_info->realm = apr_pstrdup(digest_info->pool, realm_name);
    digest_info->username = apr_pstrdup(digest_info->pool, username);
    digest_info->digest_nc++;

    status = build_digest_ha1(&digest_info->ha1, username, password,
                              digest_info->realm, digest_info->pool);

    apr_pool_destroy(cred_pool);

    /* If the handshake is finished tell serf it can send as much requests as it
       likes. */
    serf_connection_set_max_outstanding_requests(conn, 0);

    return status;
}