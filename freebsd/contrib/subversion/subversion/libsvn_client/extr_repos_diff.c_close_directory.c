#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct edit_baton {TYPE_2__* processor; int /*<<< orphan*/  ra_session; int /*<<< orphan*/ * empty_hash; } ;
struct dir_baton {int /*<<< orphan*/ * pool; int /*<<< orphan*/  pdb; int /*<<< orphan*/  right_source; int /*<<< orphan*/  left_source; int /*<<< orphan*/  path; int /*<<< orphan*/  skip; TYPE_1__* propchanges; scalar_t__ added; int /*<<< orphan*/  base_revision; scalar_t__ has_propchange; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* dir_closed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dir_changed ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dir_added ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {scalar_t__ nelts; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  release_dir (struct dir_baton*) ; 
 int /*<<< orphan*/  remove_non_prop_changes (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop__patch (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_dir2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_directory(void *dir_baton,
                apr_pool_t *pool)
{
  struct dir_baton *db = dir_baton;
  struct edit_baton *eb = db->edit_baton;
  apr_pool_t *scratch_pool;
  apr_hash_t *pristine_props;
  svn_boolean_t send_changed = FALSE;

  scratch_pool = db->pool;

  if ((db->has_propchange || db->added) && !db->skip)
    {
      if (db->added)
        {
          pristine_props = eb->empty_hash;
        }
      else
        {
          SVN_ERR(svn_ra_get_dir2(eb->ra_session, NULL, NULL, &pristine_props,
                                  db->path, db->base_revision, 0, scratch_pool));
        }

      if (db->propchanges->nelts > 0)
        {
          remove_non_prop_changes(pristine_props, db->propchanges);
        }

      if (db->propchanges->nelts > 0 || db->added)
        {
          apr_hash_t *right_props;

          right_props = svn_prop__patch(pristine_props, db->propchanges,
                                        scratch_pool);

          if (db->added)
            {
              SVN_ERR(eb->processor->dir_added(db->path,
                                           NULL /* copyfrom */,
                                           db->right_source,
                                           NULL /* copyfrom props */,
                                           right_props,
                                           db->pdb,
                                           eb->processor,
                                           db->pool));
            }
          else
            {
              SVN_ERR(eb->processor->dir_changed(db->path,
                                                 db->left_source,
                                                 db->right_source,
                                                 pristine_props,
                                                 right_props,
                                                 db->propchanges,
                                                 db->pdb,
                                                 eb->processor,
                                                 db->pool));
            }

          send_changed = TRUE; /* Skip dir_closed */
        }
    }

  if (! db->skip && !send_changed)
    {
      SVN_ERR(eb->processor->dir_closed(db->path,
                                        db->left_source,
                                        db->right_source,
                                        db->pdb,
                                        eb->processor,
                                        db->pool));
    }
  SVN_ERR(release_dir(db));

  return SVN_NO_ERROR;
}