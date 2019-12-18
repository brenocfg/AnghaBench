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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  check_working_copy; } ;
struct edit_baton {TYPE_1__ wb; int /*<<< orphan*/  db; int /*<<< orphan*/ * target_basename; int /*<<< orphan*/  anchor_abspath; } ;
struct dir_baton {char const* local_abspath; struct dir_baton* parent_baton; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_status_deleted ; 
 int /*<<< orphan*/  svn_wc_status_modified ; 
 int /*<<< orphan*/  tweak_statushash (struct dir_baton*,struct dir_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
delete_entry(const char *path,
             svn_revnum_t revision,
             void *parent_baton,
             apr_pool_t *pool)
{
  struct dir_baton *db = parent_baton;
  struct edit_baton *eb = db->edit_baton;
  const char *local_abspath = svn_dirent_join(eb->anchor_abspath, path, pool);

  /* Note:  when something is deleted, it's okay to tweak the
     statushash immediately.  No need to wait until close_file or
     close_dir, because there's no risk of having to honor the 'added'
     flag.  We already know this item exists in the working copy. */
  SVN_ERR(tweak_statushash(db, db, TRUE, eb->db, eb->wb.check_working_copy,
                           local_abspath,
                           svn_wc_status_deleted, 0, 0, revision, NULL, pool));

  /* Mark the parent dir -- it lost an entry (unless that parent dir
     is the root node and we're not supposed to report on the root
     node).  */
  if (db->parent_baton && (! *eb->target_basename))
    SVN_ERR(tweak_statushash(db->parent_baton, db, TRUE,
                             eb->db, eb->wb.check_working_copy,
                             db->local_abspath,
                             svn_wc_status_modified, svn_wc_status_modified,
                             0, SVN_INVALID_REVNUM, NULL, pool));

  return SVN_NO_ERROR;
}