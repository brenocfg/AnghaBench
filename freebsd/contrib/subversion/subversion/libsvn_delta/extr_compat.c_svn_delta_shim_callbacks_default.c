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
typedef  int /*<<< orphan*/  svn_delta_shim_callbacks_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_delta_shim_callbacks_t *
svn_delta_shim_callbacks_default(apr_pool_t *result_pool)
{
  svn_delta_shim_callbacks_t *shim_callbacks = apr_pcalloc(result_pool,
                                                     sizeof(*shim_callbacks));
  return shim_callbacks;
}