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
typedef  int /*<<< orphan*/  svn_ra_callbacks2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_error_t *
svn_ra_create_callbacks(svn_ra_callbacks2_t **callbacks,
                        apr_pool_t *pool)
{
  *callbacks = apr_pcalloc(pool, sizeof(**callbacks));
  return SVN_NO_ERROR;
}