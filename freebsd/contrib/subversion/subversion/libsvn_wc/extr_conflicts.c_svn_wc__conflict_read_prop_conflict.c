#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_6__ {scalar_t__ is_atom; struct TYPE_6__* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; struct TYPE_6__* children; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_MISSING ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CONFLICT_KIND_PROP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conflict__get_conflict (TYPE_1__**,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  svn_skel__parse_proplist (int /*<<< orphan*/ **,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__conflict_read_prop_conflict(const char **marker_abspath,
                                    apr_hash_t **mine_props,
                                    apr_hash_t **their_old_props,
                                    apr_hash_t **their_props,
                                    apr_hash_t **conflicted_prop_names,
                                    svn_wc__db_t *db,
                                    const char *wri_abspath,
                                    const svn_skel_t *conflict_skel,
                                    apr_pool_t *result_pool,
                                    apr_pool_t *scratch_pool)
{
  svn_skel_t *prop_conflict;
  const svn_skel_t *c;

  SVN_ERR(conflict__get_conflict(&prop_conflict, conflict_skel,
                                 SVN_WC__CONFLICT_KIND_PROP));

  if (!prop_conflict)
    return svn_error_create(SVN_ERR_WC_MISSING, NULL, _("Conflict not set"));

  c = prop_conflict->children;

  c = c->next; /* Skip "prop" */

  /* Get marker file */
  if (marker_abspath)
    {
      const char *marker_relpath;

      if (c->children && c->children->is_atom)
        {
          marker_relpath = apr_pstrmemdup(result_pool, c->children->data,
                                        c->children->len);

          SVN_ERR(svn_wc__db_from_relpath(marker_abspath, db, wri_abspath,
                                          marker_relpath,
                                          result_pool, scratch_pool));
        }
      else
        *marker_abspath = NULL;
    }
  c = c->next;

  /* Get conflicted properties */
  if (conflicted_prop_names)
    {
      const svn_skel_t *name;
      *conflicted_prop_names = apr_hash_make(result_pool);

      for (name = c->children; name; name = name->next)
        {
          svn_hash_sets(*conflicted_prop_names,
                        apr_pstrmemdup(result_pool, name->data, name->len),
                        "");
        }
    }
  c = c->next;

  /* Get original properties */
  if (their_old_props)
    {
      if (c->is_atom)
        *their_old_props = apr_hash_make(result_pool);
      else
        SVN_ERR(svn_skel__parse_proplist(their_old_props, c, result_pool));
    }
  c = c->next;

  /* Get mine properties */
  if (mine_props)
    {
      if (c->is_atom)
        *mine_props = apr_hash_make(result_pool);
      else
        SVN_ERR(svn_skel__parse_proplist(mine_props, c, result_pool));
    }
  c = c->next;

  /* Get their properties */
  if (their_props)
    {
      if (c->is_atom)
        *their_props = apr_hash_make(result_pool);
      else
        SVN_ERR(svn_skel__parse_proplist(their_props, c, result_pool));
    }

  return SVN_NO_ERROR;
}