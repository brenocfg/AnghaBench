#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  pool; int /*<<< orphan*/ * repos; } ;
typedef  TYPE_1__ config_access_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  handle_missing_file (int /*<<< orphan*/ **,int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * representation_stream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_ancestor (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_check_path (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_file_checksum (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 char* svn_repos_find_root_path (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_open3 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_repos_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_get_dirent_from_file_url (char const**,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_repos_config(svn_stream_t **stream,
                 svn_checksum_t **checksum,
                 config_access_t *access,
                 const char *url,
                 svn_boolean_t must_exist,
                 apr_pool_t *scratch_pool)
{
  svn_fs_t *fs;
  svn_fs_root_t *root;
  svn_revnum_t youngest_rev;
  svn_node_kind_t node_kind;
  const char *dirent;
  const char *fs_path;
  const char *repos_root_dirent;

  SVN_ERR(svn_uri_get_dirent_from_file_url(&dirent, url, access->pool));

  /* Maybe we can use the repos hint instance instead of creating a
   * new one. */
  if (access->repos)
    {
      repos_root_dirent = svn_repos_path(access->repos, scratch_pool);
      if (!svn_dirent_is_absolute(repos_root_dirent))
        SVN_ERR(svn_dirent_get_absolute(&repos_root_dirent,
                                        repos_root_dirent,
                                        scratch_pool));

      if (!svn_dirent_is_ancestor(repos_root_dirent, dirent))
        access->repos = NULL;
    }

  /* Open repos if no suitable repos is available. */
  if (!access->repos)
    {
      /* Search for a repository in the full path. */
      repos_root_dirent = svn_repos_find_root_path(dirent, scratch_pool);

      /* Attempt to open a repository at repos_root_dirent. */
      SVN_ERR(svn_repos_open3(&access->repos, repos_root_dirent, NULL,
                              access->pool, scratch_pool));
    }

  fs_path = &dirent[strlen(repos_root_dirent)];

  /* Get the filesystem. */
  fs = svn_repos_fs(access->repos);

  /* Find HEAD and the revision root */
  SVN_ERR(svn_fs_youngest_rev(&youngest_rev, fs, scratch_pool));
  SVN_ERR(svn_fs_revision_root(&root, fs, youngest_rev, access->pool));

  /* Special case: non-existent paths may be handled as "empty" contents. */
  SVN_ERR(svn_fs_check_path(&node_kind, root, fs_path, scratch_pool));
  if (node_kind != svn_node_file)
    return svn_error_trace(handle_missing_file(stream, checksum, access,
                                               url, must_exist, node_kind));

  /* Fetch checksum and see whether we already have a matching config */
  SVN_ERR(svn_fs_file_checksum(checksum, svn_checksum_md5, root, fs_path,
                               TRUE, access->pool));

  *stream = representation_stream(root, fs_path, access->pool);

  return SVN_NO_ERROR;
}