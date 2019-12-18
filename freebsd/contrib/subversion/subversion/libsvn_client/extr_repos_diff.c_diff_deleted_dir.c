#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_dirent_t ;
typedef  int /*<<< orphan*/  svn_diff_source_t ;
typedef  scalar_t__ svn_boolean_t ;
struct edit_baton {TYPE_2__* processor; int /*<<< orphan*/  revision; int /*<<< orphan*/  ra_session; int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/ * (* cancel_func ) (int /*<<< orphan*/ ) ;} ;
struct dir_baton {int /*<<< orphan*/  pdb; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_6__ {int /*<<< orphan*/ * (* dir_deleted ) (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* dir_opened ) (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_DIRENT_KIND ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * diff_deleted_file (char const*,struct dir_baton*,int /*<<< orphan*/ *) ; 
 struct dir_baton* make_dir_baton (char const*,struct dir_baton*,struct edit_baton*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * release_dir (struct dir_baton*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub3 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_diff__source_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
diff_deleted_dir(const char *path,
                 struct dir_baton *pb,
                 apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = pb->edit_baton;
  struct dir_baton *db;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  svn_boolean_t skip = FALSE;
  svn_boolean_t skip_children = FALSE;
  apr_hash_t *dirents = NULL;
  apr_hash_t *left_props = NULL;
  svn_diff_source_t *left_source = svn_diff__source_create(eb->revision,
                                                           scratch_pool);
  db = make_dir_baton(path, pb, pb->edit_baton, FALSE, SVN_INVALID_REVNUM,
                      scratch_pool);

  SVN_ERR_ASSERT(SVN_IS_VALID_REVNUM(eb->revision));

  if (eb->cancel_func)
    SVN_ERR(eb->cancel_func(eb->cancel_baton));

  SVN_ERR(eb->processor->dir_opened(&db->pdb, &skip, &skip_children,
                                    path,
                                    left_source,
                                    NULL /* right_source */,
                                    NULL /* copyfrom_source */,
                                    pb->pdb,
                                    eb->processor,
                                    scratch_pool, iterpool));

  if (!skip || !skip_children)
    SVN_ERR(svn_ra_get_dir2(eb->ra_session,
                            skip_children ? NULL : &dirents,
                            NULL,
                            skip ? NULL : &left_props,
                            path,
                            eb->revision,
                            SVN_DIRENT_KIND,
                            scratch_pool));

  /* The "old" dir will be skipped by the repository report.  If required,
   * crawl it recursively, diffing each file against the empty file.  This
   * is a workaround for issue 2333 "'svn diff URL1 URL2' not reverse of
   * 'svn diff URL2 URL1'". */
  if (! skip_children)
    {
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(scratch_pool, dirents); hi;
           hi = apr_hash_next(hi))
        {
          const char *child_path;
          const char *name = apr_hash_this_key(hi);
          svn_dirent_t *dirent = apr_hash_this_val(hi);

          svn_pool_clear(iterpool);

          child_path = svn_relpath_join(path, name, iterpool);

          if (dirent->kind == svn_node_file)
            {
              SVN_ERR(diff_deleted_file(child_path, db, iterpool));
            }
          else if (dirent->kind == svn_node_dir)
            {
              SVN_ERR(diff_deleted_dir(child_path, db, iterpool));
            }
        }
    }

  if (! skip)
    {
      SVN_ERR(eb->processor->dir_deleted(path,
                                         left_source,
                                         left_props,
                                         db->pdb,
                                         eb->processor,
                                         scratch_pool));
    }

  SVN_ERR(release_dir(db));

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}