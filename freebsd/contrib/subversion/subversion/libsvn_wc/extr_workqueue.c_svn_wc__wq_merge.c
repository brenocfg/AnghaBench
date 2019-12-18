#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* children; } ;
typedef  TYPE_1__ svn_skel_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ SVN_WC__SINGLE_WORK_ITEM (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_skel__append (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (TYPE_1__*,TYPE_1__*) ; 

svn_skel_t *
svn_wc__wq_merge(svn_skel_t *work_item1,
                 svn_skel_t *work_item2,
                 apr_pool_t *result_pool)
{
  /* If either argument is NULL, then just return the other.  */
  if (work_item1 == NULL)
    return work_item2;
  if (work_item2 == NULL)
    return work_item1;

  /* We have two items. Figure out how to join them.  */
  if (SVN_WC__SINGLE_WORK_ITEM(work_item1))
    {
      if (SVN_WC__SINGLE_WORK_ITEM(work_item2))
        {
          /* Both are singular work items. Construct a list, then put
             both work items into it (in the proper order).  */

          svn_skel_t *result = svn_skel__make_empty_list(result_pool);

          svn_skel__prepend(work_item2, result);
          svn_skel__prepend(work_item1, result);
          return result;
        }

      /* WORK_ITEM2 is a list of work items. We can simply shove WORK_ITEM1
         in the front to keep the ordering.  */
      svn_skel__prepend(work_item1, work_item2);
      return work_item2;
    }
  /* WORK_ITEM1 is a list of work items.  */

  if (SVN_WC__SINGLE_WORK_ITEM(work_item2))
    {
      /* Put WORK_ITEM2 onto the end of the WORK_ITEM1 list.  */
      svn_skel__append(work_item1, work_item2);
      return work_item1;
    }

  /* We have two lists of work items. We need to chain all of the work
     items into one big list. We will leave behind the WORK_ITEM2 skel,
     as we only want its children.  */
  svn_skel__append(work_item1, work_item2->children);
  return work_item1;
}