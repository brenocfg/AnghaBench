#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int dummy; } ;
struct dir_baton {int /*<<< orphan*/  deleted_entries; struct edit_baton* edit_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {int nelts; } ;
typedef  TYPE_1__ apr_array_header_t ;
struct TYPE_6__ {char* key; } ;

/* Variables and functions */
 TYPE_3__ APR_ARRAY_IDX (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  dump_node (struct edit_baton*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_action_delete ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_sort__hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort__item_t ; 
 int /*<<< orphan*/  svn_sort_compare_items_lexically ; 

__attribute__((used)) static svn_error_t *
close_directory(void *dir_baton,
                apr_pool_t *pool)
{
  struct dir_baton *db = dir_baton;
  struct edit_baton *eb = db->edit_baton;
  apr_pool_t *subpool = svn_pool_create(pool);
  int i;
  apr_array_header_t *sorted_entries;

  /* Sort entries lexically instead of as paths. Even though the entries
   * are full paths they're all in the same directory (see comment in struct
   * dir_baton definition). So we really want to sort by basename, in which
   * case the lexical sort function is more efficient. */
  sorted_entries = svn_sort__hash(db->deleted_entries,
                                  svn_sort_compare_items_lexically, pool);
  for (i = 0; i < sorted_entries->nelts; i++)
    {
      const char *path = APR_ARRAY_IDX(sorted_entries, i,
                                       svn_sort__item_t).key;

      svn_pool_clear(subpool);

      /* By sending 'svn_node_unknown', the Node-kind: header simply won't
         be written out.  No big deal at all, really.  The loader
         shouldn't care.  */
      SVN_ERR(dump_node(eb, path,
                        svn_node_unknown, svn_node_action_delete,
                        FALSE, NULL, SVN_INVALID_REVNUM, subpool));
    }

  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}