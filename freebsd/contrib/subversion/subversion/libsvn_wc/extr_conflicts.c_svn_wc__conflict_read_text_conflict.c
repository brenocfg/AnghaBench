#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; scalar_t__ is_atom; struct TYPE_9__* next; TYPE_2__* children; } ;
typedef  TYPE_3__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {TYPE_1__* next; } ;
struct TYPE_7__ {TYPE_3__* children; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_MISSING ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CONFLICT_KIND_TEXT ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conflict__get_conflict (TYPE_3__**,TYPE_3__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__conflict_read_text_conflict(const char **mine_abspath,
                                    const char **their_old_abspath,
                                    const char **their_abspath,
                                    svn_wc__db_t *db,
                                    const char *wri_abspath,
                                    const svn_skel_t *conflict_skel,
                                    apr_pool_t *result_pool,
                                    apr_pool_t *scratch_pool)
{
  svn_skel_t *text_conflict;
  const svn_skel_t *m;

  SVN_ERR(conflict__get_conflict(&text_conflict, conflict_skel,
                                 SVN_WC__CONFLICT_KIND_TEXT));

  if (!text_conflict)
    return svn_error_create(SVN_ERR_WC_MISSING, NULL, _("Conflict not set"));

  m = text_conflict->children->next->children;

  if (their_old_abspath)
    {
      if (m->is_atom)
        {
          const char *original_relpath;

          original_relpath = apr_pstrmemdup(scratch_pool, m->data, m->len);
          SVN_ERR(svn_wc__db_from_relpath(their_old_abspath,
                                          db, wri_abspath, original_relpath,
                                          result_pool, scratch_pool));
        }
      else
        *their_old_abspath = NULL;
    }
  m = m->next;

  if (mine_abspath)
    {
      if (m->is_atom)
        {
          const char *mine_relpath;

          mine_relpath = apr_pstrmemdup(scratch_pool, m->data, m->len);
          SVN_ERR(svn_wc__db_from_relpath(mine_abspath,
                                          db, wri_abspath, mine_relpath,
                                          result_pool, scratch_pool));
        }
      else
        *mine_abspath = NULL;
    }
  m = m->next;

  if (their_abspath)
    {
      if (m->is_atom)
        {
          const char *their_relpath;

          their_relpath = apr_pstrmemdup(scratch_pool, m->data, m->len);
          SVN_ERR(svn_wc__db_from_relpath(their_abspath,
                                          db, wri_abspath, their_relpath,
                                          result_pool, scratch_pool));
        }
      else
        *their_abspath = NULL;
    }

  return SVN_NO_ERROR;
}