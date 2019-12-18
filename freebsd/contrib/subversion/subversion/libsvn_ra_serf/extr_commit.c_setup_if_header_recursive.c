#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_stringbuf_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_12__ {TYPE_1__* session; int /*<<< orphan*/  deleted_entries; int /*<<< orphan*/  lock_tokens; } ;
typedef  TYPE_3__ commit_context_t ;
struct TYPE_13__ {char* path; } ;
typedef  TYPE_4__ apr_uri_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_10__ {TYPE_4__ session_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char* apr_uri_unparse (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serf_bucket_headers_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_path_url_add_component2 (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_skip_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbyte (TYPE_2__*,char) ; 
 int /*<<< orphan*/  svn_stringbuf_appendcstr (TYPE_2__*,char*) ; 
 TYPE_2__* svn_stringbuf_create (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
setup_if_header_recursive(svn_boolean_t *added,
                          serf_bucket_t *headers,
                          commit_context_t *commit_ctx,
                          const char *rq_relpath,
                          apr_pool_t *pool)
{
  svn_stringbuf_t *sb = NULL;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = NULL;

  if (!commit_ctx->lock_tokens)
    {
      *added = FALSE;
      return SVN_NO_ERROR;
    }

  /* We try to create a directory, so within the Subversion world that
     would imply that there is nothing here, but mod_dav_svn still sees
     locks on the old nodes here as in DAV it is perfectly legal to lock
     something that is not there...

     Let's make mod_dav, mod_dav_svn and the DAV RFC happy by providing
     the locks we know of with the request */

  for (hi = apr_hash_first(pool, commit_ctx->lock_tokens);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *relpath = apr_hash_this_key(hi);
      apr_uri_t uri;

      if (!svn_relpath_skip_ancestor(rq_relpath, relpath))
        continue;
      else if (svn_hash_gets(commit_ctx->deleted_entries, relpath))
        {
          /* When a path is already explicit deleted then its lock
             will be removed by mod_dav. But mod_dav doesn't remove
             locks on descendants */
          continue;
        }

      if (!iterpool)
        iterpool = svn_pool_create(pool);
      else
        svn_pool_clear(iterpool);

      if (sb == NULL)
        sb = svn_stringbuf_create("", pool);
      else
        svn_stringbuf_appendbyte(sb, ' ');

      uri = commit_ctx->session->session_url;
      uri.path = (char *)svn_path_url_add_component2(uri.path, relpath,
                                                    iterpool);

      svn_stringbuf_appendbyte(sb, '<');
      svn_stringbuf_appendcstr(sb, apr_uri_unparse(iterpool, &uri, 0));
      svn_stringbuf_appendcstr(sb, "> (<");
      svn_stringbuf_appendcstr(sb, apr_hash_this_val(hi));
      svn_stringbuf_appendcstr(sb, ">)");
    }

  if (iterpool)
    svn_pool_destroy(iterpool);

  if (sb)
    {
      serf_bucket_headers_set(headers, "If", sb->data);
      *added = TRUE;
    }
  else
    *added = FALSE;

  return SVN_NO_ERROR;
}