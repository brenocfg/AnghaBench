#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  rev; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {char const* root_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ILLEGAL_TARGET ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_file_ev2 (struct edit_baton*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  append_basename_if_dir (char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_unknown ; 
 scalar_t__ svn_path_is_empty (char const*) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_ra_get_file (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_buffered (int /*<<< orphan*/ *) ; 
 char* svn_uri_basename (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
export_file_ev2(const char *from_url,
                const char *to_path,
                struct edit_baton *eb,
                svn_client__pathrev_t *loc,
                svn_ra_session_t *ra_session,
                svn_boolean_t overwrite,
                apr_pool_t *scratch_pool)
{
  apr_hash_t *props;
  svn_stream_t *tmp_stream;
  svn_node_kind_t to_kind;

  SVN_ERR_ASSERT(svn_path_is_url(from_url));

  if (svn_path_is_empty(to_path))
    {
      to_path = svn_uri_basename(from_url, scratch_pool);
      eb->root_path = to_path;
    }
  else
    {
      SVN_ERR(append_basename_if_dir(&to_path, from_url,
                                     TRUE, scratch_pool));
      eb->root_path = to_path;
    }

  SVN_ERR(svn_io_check_path(to_path, &to_kind, scratch_pool));

  if ((to_kind == svn_node_file || to_kind == svn_node_unknown) &&
      ! overwrite)
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("Destination file '%s' exists, and "
                               "will not be overwritten unless forced"),
                             svn_dirent_local_style(to_path, scratch_pool));
  else if (to_kind == svn_node_dir)
    return svn_error_createf(SVN_ERR_ILLEGAL_TARGET, NULL,
                             _("Destination '%s' exists. Cannot "
                               "overwrite directory with non-directory"),
                             svn_dirent_local_style(to_path, scratch_pool));

  tmp_stream = svn_stream_buffered(scratch_pool);

  SVN_ERR(svn_ra_get_file(ra_session, "", loc->rev,
                          tmp_stream, NULL, &props, scratch_pool));

  /* Since you cannot actually root an editor at a file, we manually drive
   * a function of our editor. */
  SVN_ERR(add_file_ev2(eb, "", NULL, tmp_stream, props, SVN_INVALID_REVNUM,
                       scratch_pool));

  return SVN_NO_ERROR;
}