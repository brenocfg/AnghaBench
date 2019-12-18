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
struct TYPE_4__ {int /*<<< orphan*/ * pool; int /*<<< orphan*/  rev_roots; } ;
typedef  TYPE_1__ svn_branch__repos_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_branch__repos_t *
svn_branch__repos_create(apr_pool_t *result_pool)
{
  svn_branch__repos_t *repos = apr_pcalloc(result_pool, sizeof(*repos));

  repos->rev_roots = apr_array_make(result_pool, 0, sizeof(void *));
  repos->pool = result_pool;
  return repos;
}