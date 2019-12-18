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
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {char const* path; struct edit_baton* edit_baton; } ;
struct edit_baton {int /*<<< orphan*/  txn_root; int /*<<< orphan*/  base_path; } ;
struct dir_baton {struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct file_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_authz (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_out_of_date (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_authz_read ; 
 int /*<<< orphan*/  svn_fs_node_created_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_file(const char *path,
          void *parent_baton,
          svn_revnum_t base_revision,
          apr_pool_t *pool,
          void **file_baton)
{
  struct file_baton *new_fb;
  struct dir_baton *pb = parent_baton;
  struct edit_baton *eb = pb->edit_baton;
  svn_revnum_t cr_rev;
  apr_pool_t *subpool = svn_pool_create(pool);
  const char *full_path;

  full_path = svn_fspath__join(eb->base_path,
                               svn_relpath_canonicalize(path, pool), pool);

  /* Check for read authorization. */
  SVN_ERR(check_authz(eb, full_path, eb->txn_root,
                      svn_authz_read, subpool));

  /* Get this node's creation revision (doubles as an existence check). */
  SVN_ERR(svn_fs_node_created_rev(&cr_rev, eb->txn_root, full_path,
                                  subpool));

  /* If the node our caller has is an older revision number than the
     one in our transaction, return an out-of-dateness error. */
  if (SVN_IS_VALID_REVNUM(base_revision))
    SVN_ERR(check_out_of_date(eb, full_path, svn_node_file,
                              base_revision, cr_rev));

  /* Build a new file baton */
  new_fb = apr_pcalloc(pool, sizeof(*new_fb));
  new_fb->edit_baton = eb;
  new_fb->path = full_path;

  *file_baton = new_fb;

  /* Destory the work subpool. */
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}