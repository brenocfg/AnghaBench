#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_11__ {TYPE_1__* children; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_WC__CONFLICT_KIND_TEXT ; 
 int /*<<< orphan*/  conflict__get_conflict (TYPE_2__**,TYPE_2__*,char const*) ; 
 TYPE_2__* svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (char const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_to_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__conflict_skel_add_text_conflict(svn_skel_t *conflict_skel,
                                        svn_wc__db_t *db,
                                        const char *wri_abspath,
                                        const char *mine_abspath,
                                        const char *their_old_abspath,
                                        const char *their_abspath,
                                        apr_pool_t *result_pool,
                                        apr_pool_t *scratch_pool)
{
  svn_skel_t *text_conflict;
  svn_skel_t *markers;

  SVN_ERR(conflict__get_conflict(&text_conflict, conflict_skel,
                                 SVN_WC__CONFLICT_KIND_TEXT));

  SVN_ERR_ASSERT(!text_conflict); /* ### Use proper error? */

  /* Current skel format
     ("text"
      (OLD MINE OLD-THEIRS THEIRS)) */

  text_conflict = svn_skel__make_empty_list(result_pool);
  markers = svn_skel__make_empty_list(result_pool);

if (their_abspath)
    {
      const char *their_relpath;

      SVN_ERR(svn_wc__db_to_relpath(&their_relpath,
                                    db, wri_abspath, their_abspath,
                                    result_pool, scratch_pool));
      svn_skel__prepend_str(their_relpath, markers, result_pool);
    }
  else
    svn_skel__prepend(svn_skel__make_empty_list(result_pool), markers);

  if (mine_abspath)
    {
      const char *mine_relpath;

      SVN_ERR(svn_wc__db_to_relpath(&mine_relpath,
                                    db, wri_abspath, mine_abspath,
                                    result_pool, scratch_pool));
      svn_skel__prepend_str(mine_relpath, markers, result_pool);
    }
  else
    svn_skel__prepend(svn_skel__make_empty_list(result_pool), markers);

  if (their_old_abspath)
    {
      const char *original_relpath;

      SVN_ERR(svn_wc__db_to_relpath(&original_relpath,
                                    db, wri_abspath, their_old_abspath,
                                    result_pool, scratch_pool));
      svn_skel__prepend_str(original_relpath, markers, result_pool);
    }
  else
    svn_skel__prepend(svn_skel__make_empty_list(result_pool), markers);

  svn_skel__prepend(markers, text_conflict);
  svn_skel__prepend_str(SVN_WC__CONFLICT_KIND_TEXT, text_conflict,
                        result_pool);

  /* And add it to the conflict skel */
  svn_skel__prepend(text_conflict, conflict_skel->children->next);

  return SVN_NO_ERROR;
}