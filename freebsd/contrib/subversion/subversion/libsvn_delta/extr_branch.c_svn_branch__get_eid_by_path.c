#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  e_map; } ;
typedef  TYPE_1__ svn_element__tree_t ;
typedef  int /*<<< orphan*/  svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_branch__state_get_elements (int /*<<< orphan*/  const*,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int svn_eid__hash_this_key (int /*<<< orphan*/ *) ; 
 char* svn_element__tree_get_path_by_eid (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 

int
svn_branch__get_eid_by_path(const svn_branch__state_t *branch,
                            const char *path,
                            apr_pool_t *scratch_pool)
{
  svn_element__tree_t *elements;
  apr_hash_index_t *hi;

  /*SVN_ERR_ASSERT_NO_RETURN(branch->priv->is_flat);*/

  /* ### This is a crude, linear search */
  svn_error_clear(svn_branch__state_get_elements(branch, &elements, scratch_pool));
  for (hi = apr_hash_first(scratch_pool, elements->e_map);
       hi; hi = apr_hash_next(hi))
    {
      int eid = svn_eid__hash_this_key(hi);
      const char *this_path = svn_element__tree_get_path_by_eid(elements, eid,
                                                                scratch_pool);

      if (! this_path)
        {
          /* Mapping is not complete; this element is in effect not present. */
          continue;
        }
      if (strcmp(path, this_path) == 0)
        {
          return eid;
        }
    }

  return -1;
}