#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_DATE ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_REV ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LAST_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_UUID ; 
 int /*<<< orphan*/  svn_fs_node_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_get_committed_info (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_createf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_node_props(apr_hash_t **props,
               svn_fs_root_t *root,
               const char *path,
               const char *uuid,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  svn_revnum_t cmt_rev;
  const char *cmt_date, *cmt_author;

  /* Create a hash with props attached to the fs node. */
  SVN_ERR(svn_fs_node_proplist(props, root, path, result_pool));

  /* Now add some non-tweakable metadata to the hash as well... */

  /* The so-called 'entryprops' with info about CR & friends. */
  SVN_ERR(svn_repos_get_committed_info(&cmt_rev, &cmt_date,
                                       &cmt_author, root, path,
                                       scratch_pool));

  svn_hash_sets(*props, SVN_PROP_ENTRY_COMMITTED_REV,
                svn_string_createf(result_pool, "%ld", cmt_rev));
  svn_hash_sets(*props, SVN_PROP_ENTRY_COMMITTED_DATE, cmt_date ?
                svn_string_create(cmt_date, result_pool) : NULL);
  svn_hash_sets(*props, SVN_PROP_ENTRY_LAST_AUTHOR, cmt_author ?
                svn_string_create(cmt_author, result_pool) : NULL);
  svn_hash_sets(*props, SVN_PROP_ENTRY_UUID,
                svn_string_create(uuid, result_pool));

  /* We have no 'wcprops' in ra_local, but might someday. */

  return SVN_NO_ERROR;
}