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
typedef  int /*<<< orphan*/  apr_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/ * common_pool ; 
 scalar_t__ common_pool_initialized ; 
 int /*<<< orphan*/ * common_pool_lock ; 

__attribute__((used)) static apr_status_t uninit(void *data)
{
  common_pool = NULL;
  common_pool_lock = NULL;
  common_pool_initialized = 0;

  return APR_SUCCESS;
}