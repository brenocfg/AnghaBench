#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__xml_estate_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_report_t {struct replay_node_t* current_node; TYPE_1__* editor; int /*<<< orphan*/  editor_baton; struct replay_node_t* root_node; int /*<<< orphan*/ * pool; int /*<<< orphan*/  rev_props; int /*<<< orphan*/  replay_baton; int /*<<< orphan*/  revision; int /*<<< orphan*/  (* revfinish_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct replay_node_t {int file; int /*<<< orphan*/ * stream; int /*<<< orphan*/  baton; int /*<<< orphan*/ * pool; struct replay_node_t* parent; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* change_dir_prop ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* change_file_prop ) (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* delete_entry ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close_directory ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* close_file ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* add_file ) (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* add_directory ) (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_file ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_directory ) (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* open_root ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_target_revision ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 void* FALSE ; 
#define  REPLAY_ADD_DIRECTORY 131 
#define  REPLAY_ADD_FILE 130 
 int REPLAY_APPLY_TEXTDELTA ; 
 int REPLAY_CHANGE_DIRECTORY_PROP ; 
 int REPLAY_CHANGE_FILE_PROP ; 
 int REPLAY_CLOSE_DIRECTORY ; 
 int REPLAY_CLOSE_FILE ; 
 int REPLAY_DELETE_ENTRY ; 
#define  REPLAY_OPEN_DIRECTORY 129 
#define  REPLAY_OPEN_FILE 128 
 int REPLAY_OPEN_ROOT ; 
 int REPLAY_REPORT ; 
 int REPLAY_TARGET_REVISION ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_XML_MALFORMED ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* TRUE ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_base64_decode_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cstring_atoi64 (scalar_t__*,char const*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
replay_closed(svn_ra_serf__xml_estate_t *xes,
              void *baton,
              int leaving_state,
              const svn_string_t *cdata,
              apr_hash_t *attrs,
              apr_pool_t *scratch_pool)
{
  struct revision_report_t *ctx = baton;

  if (leaving_state == REPLAY_REPORT)
    {
      if (ctx->current_node)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      if (ctx->revfinish_func)
        {
          SVN_ERR(ctx->revfinish_func(ctx->revision, ctx->replay_baton,
                                      ctx->editor, ctx->editor_baton,
                                      ctx->rev_props, scratch_pool));
        }
    }
  else if (leaving_state == REPLAY_TARGET_REVISION)
    {
      const char *revstr = svn_hash_gets(attrs, "rev");
      apr_int64_t rev;

      SVN_ERR(svn_cstring_atoi64(&rev, revstr));
      SVN_ERR(ctx->editor->set_target_revision(ctx->editor_baton,
                                               (svn_revnum_t)rev,
                                               scratch_pool));
    }
  else if (leaving_state == REPLAY_OPEN_ROOT)
    {
      const char *revstr = svn_hash_gets(attrs, "rev");
      apr_int64_t rev;
      apr_pool_t *root_pool = svn_pool_create(ctx->pool);

      if (ctx->current_node || ctx->root_node)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      ctx->root_node = apr_pcalloc(root_pool, sizeof(*ctx->root_node));
      ctx->root_node->pool = root_pool;

      ctx->current_node = ctx->root_node;

      SVN_ERR(svn_cstring_atoi64(&rev, revstr));
      SVN_ERR(ctx->editor->open_root(ctx->editor_baton, (svn_revnum_t)rev,
                                     root_pool,
                                     &ctx->current_node->baton));
    }
  else if (leaving_state == REPLAY_OPEN_DIRECTORY
           || leaving_state == REPLAY_OPEN_FILE
           || leaving_state == REPLAY_ADD_DIRECTORY
           || leaving_state == REPLAY_ADD_FILE)
    {
      struct replay_node_t *node;
      apr_pool_t *node_pool;
      const char *name = svn_hash_gets(attrs, "name");
      const char *rev_str;
      apr_int64_t rev;

      if (!ctx->current_node || ctx->current_node->file)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      node_pool = svn_pool_create(ctx->current_node->pool);
      node = apr_pcalloc(node_pool, sizeof(*node));
      node->pool = node_pool;
      node->parent = ctx->current_node;

      if (leaving_state == REPLAY_OPEN_DIRECTORY
          || leaving_state == REPLAY_OPEN_FILE)
        {
          rev_str = svn_hash_gets(attrs, "rev");
        }
      else
        rev_str = svn_hash_gets(attrs, "copyfrom-rev");

      if (rev_str)
        SVN_ERR(svn_cstring_atoi64(&rev, rev_str));
      else
        rev = SVN_INVALID_REVNUM;

      switch (leaving_state)
        {
          case REPLAY_OPEN_DIRECTORY:
            node->file = FALSE;
            SVN_ERR(ctx->editor->open_directory(name,
                                    ctx->current_node->baton,
                                    (svn_revnum_t)rev,
                                    node->pool,
                                    &node->baton));
            break;
          case REPLAY_OPEN_FILE:
            node->file = TRUE;
            SVN_ERR(ctx->editor->open_file(name,
                                    ctx->current_node->baton,
                                    (svn_revnum_t)rev,
                                    node->pool,
                                    &node->baton));
            break;
          case REPLAY_ADD_DIRECTORY:
            node->file = FALSE;
            SVN_ERR(ctx->editor->add_directory(
                                    name,
                                    ctx->current_node->baton,
                                    SVN_IS_VALID_REVNUM(rev)
                                        ? svn_hash_gets(attrs, "copyfrom-path")
                                        : NULL,
                                    (svn_revnum_t)rev,
                                    node->pool,
                                    &node->baton));
            break;
          case REPLAY_ADD_FILE:
            node->file = TRUE;
            SVN_ERR(ctx->editor->add_file(
                                    name,
                                    ctx->current_node->baton,
                                    SVN_IS_VALID_REVNUM(rev)
                                        ? svn_hash_gets(attrs, "copyfrom-path")
                                        : NULL,
                                    (svn_revnum_t)rev,
                                    node->pool,
                                    &node->baton));
            break;
          /* default: unreachable */
        }
      ctx->current_node = node;
    }
  else if (leaving_state == REPLAY_CLOSE_FILE)
    {
      struct replay_node_t *node = ctx->current_node;

      if (! node || ! node->file)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      SVN_ERR(ctx->editor->close_file(node->baton,
                                      svn_hash_gets(attrs, "checksum"),
                                      node->pool));
      ctx->current_node = node->parent;
      svn_pool_destroy(node->pool);
    }
  else if (leaving_state == REPLAY_CLOSE_DIRECTORY)
    {
      struct replay_node_t *node = ctx->current_node;

      if (! node || node->file)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      SVN_ERR(ctx->editor->close_directory(node->baton, node->pool));
      ctx->current_node = node->parent;
      svn_pool_destroy(node->pool);
    }
  else if (leaving_state == REPLAY_DELETE_ENTRY)
    {
      struct replay_node_t *parent_node = ctx->current_node;
      const char *name = svn_hash_gets(attrs, "name");
      const char *revstr = svn_hash_gets(attrs, "rev");
      apr_int64_t rev;

      if (! parent_node || parent_node->file)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      SVN_ERR(svn_cstring_atoi64(&rev, revstr));
      SVN_ERR(ctx->editor->delete_entry(name,
                                        (svn_revnum_t)rev,
                                        parent_node->baton,
                                        scratch_pool));
    }
  else if (leaving_state == REPLAY_CHANGE_FILE_PROP
           || leaving_state == REPLAY_CHANGE_DIRECTORY_PROP)
    {
      struct replay_node_t *node = ctx->current_node;
      const char *name;
      const svn_string_t *value;

      if (! node || node->file != (leaving_state == REPLAY_CHANGE_FILE_PROP))
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      name = svn_hash_gets(attrs, "name");

      if (svn_hash_gets(attrs, "del"))
        value = NULL;
      else
        value = svn_base64_decode_string(cdata, scratch_pool);

      if (node->file)
        {
          SVN_ERR(ctx->editor->change_file_prop(node->baton, name, value,
                                                scratch_pool));
        }
      else
        {
          SVN_ERR(ctx->editor->change_dir_prop(node->baton, name, value,
                                               scratch_pool));
        }
    }
  else if (leaving_state == REPLAY_APPLY_TEXTDELTA)
    {
      struct replay_node_t *node = ctx->current_node;

      if (! node || ! node->file)
        return svn_error_create(SVN_ERR_XML_MALFORMED, NULL, NULL);

      if (node->stream)
        SVN_ERR(svn_stream_close(node->stream));

      node->stream = NULL;
    }
  return SVN_NO_ERROR;
}