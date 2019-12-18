#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_7__ {struct TYPE_7__* next; struct TYPE_7__* children; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_INCOMPLETE_DATA ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_WC__CONFLICT_KIND_PROP ; 
 char const* SVN_WC__CONFLICT_KIND_TEXT ; 
 char const* SVN_WC__CONFLICT_KIND_TREE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  conflict__get_operation (TYPE_1__**,TYPE_1__*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_skel__matches_atom (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  svn_wc__conflict_skel_is_complete (int*,TYPE_1__*) ; 

svn_error_t *
svn_wc__conflict_skel_resolve(svn_boolean_t *completely_resolved,
                              svn_skel_t *conflict_skel,
                              svn_wc__db_t *db,
                              const char *wri_abspath,
                              svn_boolean_t resolve_text,
                              const char *resolve_prop,
                              svn_boolean_t resolve_tree,
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  svn_skel_t *op;
  svn_skel_t **pconflict;
  SVN_ERR(conflict__get_operation(&op, conflict_skel));

  if (!op)
    return svn_error_create(SVN_ERR_INCOMPLETE_DATA, NULL,
                            _("Not a completed conflict skel"));

  /* We are going to drop items from a linked list. Instead of keeping
     a pointer to the item we want to drop we store a pointer to the
     pointer of what we may drop, to allow setting it to the next item. */

  pconflict = &(conflict_skel->children->next->children);
  while (*pconflict)
    {
      svn_skel_t *c = (*pconflict)->children;

      if (resolve_text
          && svn_skel__matches_atom(c, SVN_WC__CONFLICT_KIND_TEXT))
        {
          /* Remove the text conflict from the linked list */
          *pconflict = (*pconflict)->next;
          continue;
        }
      else if (resolve_prop
               && svn_skel__matches_atom(c, SVN_WC__CONFLICT_KIND_PROP))
        {
          svn_skel_t **ppropnames = &(c->next->next->children);

          if (resolve_prop[0] == '\0')
            *ppropnames = NULL; /* remove all conflicted property names */
          else
            while (*ppropnames)
              {
                if (svn_skel__matches_atom(*ppropnames, resolve_prop))
                  {
                    *ppropnames = (*ppropnames)->next;
                    break;
                  }
                ppropnames = &((*ppropnames)->next);
              }

          /* If no conflicted property names left */
          if (!c->next->next->children)
            {
              /* Remove the propery conflict skel from the linked list */
             *pconflict = (*pconflict)->next;
             continue;
            }
        }
      else if (resolve_tree
               && svn_skel__matches_atom(c, SVN_WC__CONFLICT_KIND_TREE))
        {
          /* Remove the tree conflict from the linked list */
          *pconflict = (*pconflict)->next;
          continue;
        }

      pconflict = &((*pconflict)->next);
    }

  if (completely_resolved)
    {
      /* Nice, we can just call the complete function */
      svn_boolean_t complete_conflict;
      SVN_ERR(svn_wc__conflict_skel_is_complete(&complete_conflict,
                                                conflict_skel));

      *completely_resolved = !complete_conflict;
    }
  return SVN_NO_ERROR;
}