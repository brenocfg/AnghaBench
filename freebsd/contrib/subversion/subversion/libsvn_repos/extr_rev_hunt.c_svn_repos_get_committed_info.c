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
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_fs_node_created_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_proplist2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_repos_get_committed_info(svn_revnum_t *committed_rev,
                             const char **committed_date,
                             const char **last_author,
                             svn_fs_root_t *root,
                             const char *path,
                             apr_pool_t *pool)
{
  apr_hash_t *revprops;

  svn_fs_t *fs = svn_fs_root_fs(root);

  /* ### It might be simpler just to declare that revision
     properties have char * (i.e., UTF-8) values, not arbitrary
     binary values, hmmm. */
  svn_string_t *committed_date_s, *last_author_s;

  /* Get the CR field out of the node's skel. */
  SVN_ERR(svn_fs_node_created_rev(committed_rev, root, path, pool));

  /* Get the revision properties of this revision. */
  SVN_ERR(svn_fs_revision_proplist2(&revprops, fs, *committed_rev, TRUE,
                                    pool, pool));

  /* Extract date and author from these revprops. */
  committed_date_s = svn_hash_gets(revprops, SVN_PROP_REVISION_DATE);
  last_author_s = svn_hash_gets(revprops, SVN_PROP_REVISION_AUTHOR);

  *committed_date = committed_date_s ? committed_date_s->data : NULL;
  *last_author = last_author_s ? last_author_s->data : NULL;

  return SVN_NO_ERROR;
}