#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_9__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  working_url; int /*<<< orphan*/  name; TYPE_2__* parent_dir; scalar_t__ url; TYPE_6__* commit_ctx; } ;
typedef  TYPE_3__ dir_context_t ;
struct TYPE_10__ {char* path; } ;
typedef  TYPE_4__ apr_uri_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {TYPE_1__* session; } ;
struct TYPE_8__ {int /*<<< orphan*/  working_url; } ;
struct TYPE_7__ {TYPE_4__ session_url; } ;

/* Variables and functions */
 scalar_t__ USING_HTTPV2_COMMIT_SUPPORT (TYPE_6__*) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char*) ; 
 char* apr_uri_unparse (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  setup_add_dir_common_headers (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_path_url_add_component2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
setup_copy_dir_headers(serf_bucket_t *headers,
                       void *baton,
                       apr_pool_t *pool /* request pool */,
                       apr_pool_t *scratch_pool)
{
  dir_context_t *dir = baton;
  apr_uri_t uri;
  const char *absolute_uri;

  /* The Dest URI must be absolute.  Bummer. */
  uri = dir->commit_ctx->session->session_url;

  if (USING_HTTPV2_COMMIT_SUPPORT(dir->commit_ctx))
    {
      uri.path = (char *)dir->url;
    }
  else
    {
      uri.path = (char *)svn_path_url_add_component2(
                                    dir->parent_dir->working_url,
                                    dir->name, pool);
    }
  absolute_uri = apr_uri_unparse(pool, &uri, 0);

  serf_bucket_headers_set(headers, "Destination", absolute_uri);

  serf_bucket_headers_setn(headers, "Depth", "infinity");
  serf_bucket_headers_setn(headers, "Overwrite", "F");

  /* Implicitly checkout this dir now. */
  dir->working_url = apr_pstrdup(dir->pool, uri.path);

  return svn_error_trace(setup_add_dir_common_headers(headers, baton, pool,
                                                      scratch_pool));
}