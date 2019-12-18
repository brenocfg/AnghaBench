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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso_cache ; 
 int /*<<< orphan*/  dso_mutex ; 
 int /*<<< orphan*/  dso_pool ; 
 int /*<<< orphan*/  svn_mutex__init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
atomic_init_func(void *baton,
                 apr_pool_t *pool)
{
  dso_pool = svn_pool_create(NULL);

  SVN_ERR(svn_mutex__init(&dso_mutex, TRUE, dso_pool));

  dso_cache = apr_hash_make(dso_pool);
  return SVN_NO_ERROR;
}