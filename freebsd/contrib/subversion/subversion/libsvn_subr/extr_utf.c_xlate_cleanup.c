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
 int /*<<< orphan*/ * xlat_ntou_static_handle ; 
 int /*<<< orphan*/ * xlat_uton_static_handle ; 
 int /*<<< orphan*/ * xlate_handle_hash ; 

__attribute__((used)) static apr_status_t
xlate_cleanup(void *arg)
{
  /* We set the cache variables to NULL so that translation works in other
     cleanup functions, even if it isn't cached then. */
  xlate_handle_hash = NULL;

  /* ensure no stale objects get accessed */
  xlat_ntou_static_handle = NULL;
  xlat_uton_static_handle = NULL;

  return APR_SUCCESS;
}