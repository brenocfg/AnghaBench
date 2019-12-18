#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_8__ {scalar_t__ url; TYPE_2__* commit_ctx; } ;
typedef  TYPE_3__ file_context_t ;
struct TYPE_9__ {char* path; } ;
typedef  TYPE_4__ apr_uri_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_7__ {TYPE_1__* session; } ;
struct TYPE_6__ {TYPE_4__ session_url; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_uri_unparse (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  serf_bucket_headers_setn (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static svn_error_t *
setup_copy_file_headers(serf_bucket_t *headers,
                        void *baton,
                        apr_pool_t *pool /* request pool */,
                        apr_pool_t *scratch_pool)
{
  file_context_t *file = baton;
  apr_uri_t uri;
  const char *absolute_uri;

  /* The Dest URI must be absolute.  Bummer. */
  uri = file->commit_ctx->session->session_url;
  uri.path = (char*)file->url;
  absolute_uri = apr_uri_unparse(pool, &uri, 0);

  serf_bucket_headers_set(headers, "Destination", absolute_uri);

  serf_bucket_headers_setn(headers, "Overwrite", "F");

  return SVN_NO_ERROR;
}