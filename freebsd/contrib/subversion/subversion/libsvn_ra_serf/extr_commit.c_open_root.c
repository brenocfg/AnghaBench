#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  void* svn_revnum_t ;
struct TYPE_24__ {int code; } ;
struct TYPE_25__ {char* method; TYPE_2__ sline; struct TYPE_25__* response_baton; int /*<<< orphan*/  response_handler; void* path; TYPE_8__* commit_ctx; struct TYPE_25__* handler; int /*<<< orphan*/ * header_delegate_baton; int /*<<< orphan*/  header_delegate; int /*<<< orphan*/ * body_delegate_baton; int /*<<< orphan*/  body_delegate; int /*<<< orphan*/  body_type; } ;
typedef  TYPE_3__ svn_ra_serf__handler_t ;
struct TYPE_26__ {int /*<<< orphan*/  name; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ svn_prop_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_27__ {char const* path; void* prop_changes; int /*<<< orphan*/  base_revision; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * commit_ctx; } ;
typedef  TYPE_5__ proppatch_context_t ;
typedef  TYPE_3__ post_response_ctx_t ;
struct TYPE_28__ {char* relpath; char* name; char const* url; int /*<<< orphan*/ * pool; void* base_revision; TYPE_8__* commit_ctx; void* prop_changes; } ;
typedef  TYPE_7__ dir_context_t ;
struct TYPE_29__ {char const* txn_root_url; char* txn_url; char* baseline_url; TYPE_9__* session; int /*<<< orphan*/ * revprop_table; int /*<<< orphan*/ * pool; void* checked_in_url; int /*<<< orphan*/  vcc_url; void* activity_url; int /*<<< orphan*/  open_batons; } ;
typedef  TYPE_8__ commit_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_23__ {int /*<<< orphan*/  path; } ;
struct TYPE_30__ {char* activity_collection_url; TYPE_1__ session_url; void* me_resource; int /*<<< orphan*/  supported_posts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_DAV_REQUEST_FAILED ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (TYPE_9__*) ; 
 int /*<<< orphan*/  SVN_SKEL_MIME_TYPE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 TYPE_4__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 void* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  checkout_dir (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_txn_post_body ; 
 int /*<<< orphan*/  get_version_url (char const**,TYPE_9__*,char*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_response_handler ; 
 int /*<<< orphan*/  proppatch_resource (TYPE_9__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_post_headers ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_hash_sets (void*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 void* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__context_run_one (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_ra_serf__create_handler (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__expect_empty_body ; 
 int /*<<< orphan*/  svn_ra_serf__get_relative_path (char const**,int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__unexpected_status (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_ra_serf__v1_get_activity_collection (char const**,TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char const* svn_uuid_generate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_root(void *edit_baton,
          svn_revnum_t base_revision,
          apr_pool_t *dir_pool,
          void **root_baton)
{
  commit_context_t *commit_ctx = edit_baton;
  svn_ra_serf__handler_t *handler;
  proppatch_context_t *proppatch_ctx;
  dir_context_t *dir;
  apr_hash_index_t *hi;
  const char *proppatch_target = NULL;
  apr_pool_t *scratch_pool = svn_pool_create(dir_pool);

  commit_ctx->open_batons++;

  if (SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(commit_ctx->session))
    {
      post_response_ctx_t *prc;
      const char *rel_path;
      svn_boolean_t post_with_revprops
        = (NULL != svn_hash_gets(commit_ctx->session->supported_posts,
                                 "create-txn-with-props"));

      /* Create our activity URL now on the server. */
      handler = svn_ra_serf__create_handler(commit_ctx->session, scratch_pool);

      handler->method = "POST";
      handler->body_type = SVN_SKEL_MIME_TYPE;
      handler->body_delegate = create_txn_post_body;
      handler->body_delegate_baton =
          post_with_revprops ? commit_ctx->revprop_table : NULL;
      handler->header_delegate = setup_post_headers;
      handler->header_delegate_baton = NULL;
      handler->path = commit_ctx->session->me_resource;

      prc = apr_pcalloc(scratch_pool, sizeof(*prc));
      prc->handler = handler;
      prc->commit_ctx = commit_ctx;

      handler->response_handler = post_response_handler;
      handler->response_baton = prc;

      SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));

      if (handler->sline.code != 201)
        return svn_error_trace(svn_ra_serf__unexpected_status(handler));

      if (! (commit_ctx->txn_root_url && commit_ctx->txn_url))
        {
          return svn_error_createf(
            SVN_ERR_RA_DAV_REQUEST_FAILED, NULL,
            _("POST request did not return transaction information"));
        }

      /* Fixup the txn_root_url to point to the anchor of the commit. */
      SVN_ERR(svn_ra_serf__get_relative_path(
                                        &rel_path,
                                        commit_ctx->session->session_url.path,
                                        commit_ctx->session,
                                        scratch_pool));
      commit_ctx->txn_root_url = svn_path_url_add_component2(
                                        commit_ctx->txn_root_url,
                                        rel_path, commit_ctx->pool);

      /* Build our directory baton. */
      dir = apr_pcalloc(dir_pool, sizeof(*dir));
      dir->pool = dir_pool;
      dir->commit_ctx = commit_ctx;
      dir->base_revision = base_revision;
      dir->relpath = "";
      dir->name = "";
      dir->prop_changes = apr_hash_make(dir->pool);
      dir->url = apr_pstrdup(dir->pool, commit_ctx->txn_root_url);

      /* If we included our revprops in the POST, we need not
         PROPPATCH them. */
      proppatch_target = post_with_revprops ? NULL : commit_ctx->txn_url;
    }
  else
    {
      const char *activity_str = commit_ctx->session->activity_collection_url;

      if (!activity_str)
        SVN_ERR(svn_ra_serf__v1_get_activity_collection(
                                    &activity_str,
                                    commit_ctx->session,
                                    scratch_pool, scratch_pool));

      commit_ctx->activity_url = svn_path_url_add_component2(
                                    activity_str,
                                    svn_uuid_generate(scratch_pool),
                                    commit_ctx->pool);

      /* Create our activity URL now on the server. */
      handler = svn_ra_serf__create_handler(commit_ctx->session, scratch_pool);

      handler->method = "MKACTIVITY";
      handler->path = commit_ctx->activity_url;

      handler->response_handler = svn_ra_serf__expect_empty_body;
      handler->response_baton = handler;

      SVN_ERR(svn_ra_serf__context_run_one(handler, scratch_pool));

      if (handler->sline.code != 201)
        return svn_error_trace(svn_ra_serf__unexpected_status(handler));

      /* Now go fetch our VCC and baseline so we can do a CHECKOUT. */
      SVN_ERR(svn_ra_serf__discover_vcc(&(commit_ctx->vcc_url),
                                        commit_ctx->session, scratch_pool));


      /* Build our directory baton. */
      dir = apr_pcalloc(dir_pool, sizeof(*dir));
      dir->pool = dir_pool;
      dir->commit_ctx = commit_ctx;
      dir->base_revision = base_revision;
      dir->relpath = "";
      dir->name = "";
      dir->prop_changes = apr_hash_make(dir->pool);

      SVN_ERR(get_version_url(&dir->url, dir->commit_ctx->session,
                              dir->relpath,
                              dir->base_revision, commit_ctx->checked_in_url,
                              dir->pool, scratch_pool));
      commit_ctx->checked_in_url = apr_pstrdup(commit_ctx->pool, dir->url);

      /* Checkout our root dir */
      SVN_ERR(checkout_dir(dir, scratch_pool));

      proppatch_target = commit_ctx->baseline_url;
    }

  /* Unless this is NULL -- which means we don't need to PROPPATCH the
     transaction with our revprops -- then, you know, PROPPATCH the
     transaction with our revprops.  */
  if (proppatch_target)
    {
      proppatch_ctx = apr_pcalloc(scratch_pool, sizeof(*proppatch_ctx));
      proppatch_ctx->pool = scratch_pool;
      proppatch_ctx->commit_ctx = NULL; /* No lock info */
      proppatch_ctx->path = proppatch_target;
      proppatch_ctx->prop_changes = apr_hash_make(proppatch_ctx->pool);
      proppatch_ctx->base_revision = SVN_INVALID_REVNUM;

      for (hi = apr_hash_first(scratch_pool, commit_ctx->revprop_table);
           hi;
           hi = apr_hash_next(hi))
        {
          svn_prop_t *prop = apr_palloc(scratch_pool, sizeof(*prop));

          prop->name = apr_hash_this_key(hi);
          prop->value = apr_hash_this_val(hi);

          svn_hash_sets(proppatch_ctx->prop_changes, prop->name, prop);
        }

      SVN_ERR(proppatch_resource(commit_ctx->session,
                                 proppatch_ctx, scratch_pool));
    }

  svn_pool_destroy(scratch_pool);

  *root_baton = dir;

  return SVN_NO_ERROR;
}