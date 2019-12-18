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
typedef  int /*<<< orphan*/  u8 ;
struct ecore_ll2_stats {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_ll2_stats*,int /*<<< orphan*/ ,int) ; 
 int __ecore_ll2_get_stats (void*,int /*<<< orphan*/ ,struct ecore_ll2_stats*) ; 

enum _ecore_status_t ecore_ll2_get_stats(void *cxt,
					 u8 connection_handle,
					 struct ecore_ll2_stats	*p_stats)
{
	OSAL_MEMSET(p_stats, 0, sizeof(*p_stats));

	return __ecore_ll2_get_stats(cxt, connection_handle, p_stats);
}