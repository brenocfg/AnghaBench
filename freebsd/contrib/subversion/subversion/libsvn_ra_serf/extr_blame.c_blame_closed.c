#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
struct TYPE_4__ {char const* name; int /*<<< orphan*/  const* value; } ;
typedef  TYPE_1__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int /*<<< orphan*/  prop_diffs; int /*<<< orphan*/  rev_props; int /*<<< orphan*/  state_pool; int /*<<< orphan*/ * stream; int /*<<< orphan*/  file_rev_baton; int /*<<< orphan*/  (* file_rev ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ blame_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FILE_REV ; 
 int MERGED_REVISION ; 
 int REMOVE_PROP ; 
 int REV_PROP ; 
 int SET_PROP ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_STR_TO_REV (char const*) ; 
 int TXDELTA ; 
 TYPE_1__* apr_array_push (int /*<<< orphan*/ ) ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_base64_decode_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_ra_serf__xml_note (int /*<<< orphan*/ *,int,char*,char*) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
blame_closed(svn_ra_serf__xml_estate_t *xes,
             void *baton,
             int leaving_state,
             const svn_string_t *cdata,
             apr_hash_t *attrs,
             apr_pool_t *scratch_pool)
{
  blame_context_t *blame_ctx = baton;

  if (leaving_state == FILE_REV)
    {
      /* Note that we test STREAM, but any pointer is currently invalid.
         It was closed when left the TXDELTA state.  */
      if (blame_ctx->stream == NULL)
        {
          const char *path;
          const char *rev;

          path = svn_hash_gets(attrs, "path");
          rev = svn_hash_gets(attrs, "rev");

          /* Send a "no content" notification.  */
          SVN_ERR(blame_ctx->file_rev(blame_ctx->file_rev_baton,
                                      path, SVN_STR_TO_REV(rev),
                                      blame_ctx->rev_props,
                                      FALSE /* result_of_merge */,
                                      NULL, NULL, /* txdelta / baton */
                                      blame_ctx->prop_diffs,
                                      scratch_pool));
        }
    }
  else if (leaving_state == MERGED_REVISION)
    {
      svn_ra_serf__xml_note(xes, FILE_REV, "merged-revision", "*");
    }
  else if (leaving_state == TXDELTA)
    {
      SVN_ERR(svn_stream_close(blame_ctx->stream));
    }
  else
    {
      const char *name;
      const svn_string_t *value;

      SVN_ERR_ASSERT(leaving_state == REV_PROP
                     || leaving_state == SET_PROP
                     || leaving_state == REMOVE_PROP);

      name = apr_pstrdup(blame_ctx->state_pool,
                         svn_hash_gets(attrs, "name"));

      if (leaving_state == REMOVE_PROP)
        {
          value = NULL;
        }
      else
        {
          const char *encoding = svn_hash_gets(attrs, "encoding");

          if (encoding && strcmp(encoding, "base64") == 0)
            value = svn_base64_decode_string(cdata, blame_ctx->state_pool);
          else
            value = svn_string_dup(cdata, blame_ctx->state_pool);
        }

      if (leaving_state == REV_PROP)
        {
          svn_hash_sets(blame_ctx->rev_props, name, value);
        }
      else
        {
          svn_prop_t *prop = apr_array_push(blame_ctx->prop_diffs);

          prop->name = name;
          prop->value = value;
        }
    }

  return SVN_NO_ERROR;
}