#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_8__ {int /*<<< orphan*/  close_revision; int /*<<< orphan*/  close_node; int /*<<< orphan*/  apply_textdelta; int /*<<< orphan*/  set_fulltext; int /*<<< orphan*/  remove_node_props; int /*<<< orphan*/  delete_node_property; int /*<<< orphan*/  set_node_property; int /*<<< orphan*/  set_revision_property; int /*<<< orphan*/  new_node_record; int /*<<< orphan*/  new_revision_record; int /*<<< orphan*/  uuid_record; int /*<<< orphan*/  magic_header_record; } ;
typedef  TYPE_1__ svn_repos_parse_fns3_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct parse_baton {char const* root_url; char const* parent_dir; int /*<<< orphan*/ * skip_revprops; void* oldest_dumpstream_rev; void* last_rev_mapped; int /*<<< orphan*/  rev_map; int /*<<< orphan*/  quiet; int /*<<< orphan*/ * aux_session; int /*<<< orphan*/ * session; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVNRDUMP_PROP_LOCK ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_CANCELLED ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_ATOMIC_REVPROPS ; 
 int /*<<< orphan*/  apply_textdelta ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ *) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_node ; 
 int /*<<< orphan*/  close_revision ; 
 int /*<<< orphan*/  delete_node_property ; 
 int /*<<< orphan*/  get_lock (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  magic_header_record ; 
 int /*<<< orphan*/  new_node_record ; 
 int /*<<< orphan*/  new_revision_record ; 
 int /*<<< orphan*/  remove_node_props ; 
 int /*<<< orphan*/  set_fulltext ; 
 int /*<<< orphan*/  set_node_property ; 
 int /*<<< orphan*/  set_revision_property ; 
 TYPE_2__* svn_error_compose_create (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_ra__release_operational_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_path_relative_to_root (int /*<<< orphan*/ *,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_has_capability (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_repos_parse_dumpstream3 (int /*<<< orphan*/ *,TYPE_1__*,struct parse_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uuid_record ; 

svn_error_t *
svn_rdump__load_dumpstream(svn_stream_t *stream,
                           svn_ra_session_t *session,
                           svn_ra_session_t *aux_session,
                           svn_boolean_t quiet,
                           apr_hash_t *skip_revprops,
                           svn_cancel_func_t cancel_func,
                           void *cancel_baton,
                           apr_pool_t *pool)
{
  svn_repos_parse_fns3_t *parser;
  struct parse_baton *parse_baton;
  const svn_string_t *lock_string;
  svn_boolean_t be_atomic;
  svn_error_t *err;
  const char *session_url, *root_url, *parent_dir;

  SVN_ERR(svn_ra_has_capability(session, &be_atomic,
                                SVN_RA_CAPABILITY_ATOMIC_REVPROPS,
                                pool));
  SVN_ERR(get_lock(&lock_string, session, cancel_func, cancel_baton, pool));
  SVN_ERR(svn_ra_get_repos_root2(session, &root_url, pool));
  SVN_ERR(svn_ra_get_session_url(session, &session_url, pool));
  SVN_ERR(svn_ra_get_path_relative_to_root(session, &parent_dir,
                                           session_url, pool));

  parser = apr_pcalloc(pool, sizeof(*parser));
  parser->magic_header_record = magic_header_record;
  parser->uuid_record = uuid_record;
  parser->new_revision_record = new_revision_record;
  parser->new_node_record = new_node_record;
  parser->set_revision_property = set_revision_property;
  parser->set_node_property = set_node_property;
  parser->delete_node_property = delete_node_property;
  parser->remove_node_props = remove_node_props;
  parser->set_fulltext = set_fulltext;
  parser->apply_textdelta = apply_textdelta;
  parser->close_node = close_node;
  parser->close_revision = close_revision;

  parse_baton = apr_pcalloc(pool, sizeof(*parse_baton));
  parse_baton->session = session;
  parse_baton->aux_session = aux_session;
  parse_baton->quiet = quiet;
  parse_baton->root_url = root_url;
  parse_baton->parent_dir = parent_dir;
  parse_baton->rev_map = apr_hash_make(pool);
  parse_baton->last_rev_mapped = SVN_INVALID_REVNUM;
  parse_baton->oldest_dumpstream_rev = SVN_INVALID_REVNUM;
  parse_baton->skip_revprops = skip_revprops;

  err = svn_repos_parse_dumpstream3(stream, parser, parse_baton, FALSE,
                                    cancel_func, cancel_baton, pool);

  /* If all goes well, or if we're cancelled cleanly, don't leave a
     stray lock behind. */
  if ((! err) || (err && (err->apr_err == SVN_ERR_CANCELLED)))
    err = svn_error_compose_create(
              svn_ra__release_operational_lock(session, SVNRDUMP_PROP_LOCK,
                                               lock_string, pool),
              err);
  return err;
}