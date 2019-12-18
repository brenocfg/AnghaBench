#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_skel_t *
svn_wc__conflict_skel_create(apr_pool_t *result_pool)
{
  svn_skel_t *conflict_skel = svn_skel__make_empty_list(result_pool);

  /* Add empty CONFLICTS list */
  svn_skel__prepend(svn_skel__make_empty_list(result_pool), conflict_skel);

  /* Add empty WHY list */
  svn_skel__prepend(svn_skel__make_empty_list(result_pool), conflict_skel);

  return conflict_skel;
}