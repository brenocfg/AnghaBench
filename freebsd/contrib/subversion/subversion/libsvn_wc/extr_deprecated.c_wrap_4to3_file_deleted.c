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
typedef  int /*<<< orphan*/  svn_wc_notify_state_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct diff_callbacks3_wrapper_baton {int /*<<< orphan*/  baton; int /*<<< orphan*/  anchor; TYPE_1__* callbacks3; int /*<<< orphan*/  anchor_abspath; int /*<<< orphan*/  db; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_2__ {int /*<<< orphan*/ * (* file_deleted ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__adm_retrieve_internal2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
wrap_4to3_file_deleted(svn_wc_notify_state_t *state,
                       svn_boolean_t *tree_conflicted,
                       const char *path,
                       const char *tmpfile1,
                       const char *tmpfile2,
                       const char *mimetype1,
                       const char *mimetype2,
                       apr_hash_t *originalprops,
                       void *diff_baton,
                       apr_pool_t *scratch_pool)
{
  struct diff_callbacks3_wrapper_baton *b = diff_baton;
  svn_wc_adm_access_t *adm_access;
  const char *dir = svn_relpath_dirname(path, scratch_pool);

  adm_access = svn_wc__adm_retrieve_internal2(
                        b->db,
                        svn_dirent_join(b->anchor_abspath, dir, scratch_pool),
                        scratch_pool);

  return b->callbacks3->file_deleted(adm_access, state, tree_conflicted,
                                     svn_dirent_join(b->anchor, path,
                                                     scratch_pool),
                                     tmpfile1, tmpfile2,
                                     mimetype1, mimetype2, originalprops,
                                     b->baton);
}