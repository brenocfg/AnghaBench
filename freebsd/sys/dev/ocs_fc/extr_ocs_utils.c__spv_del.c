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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  ocs_os_handle_t ;

/* Variables and functions */
 int SPV_ROWLEN ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,void**,int) ; 

__attribute__((used)) static void
_spv_del(ocs_os_handle_t os, void **a, uint32_t n, uint32_t depth)
{
	if (a) {
		if (depth) {
			uint32_t i;

			for (i = 0; i < n; i ++) {
				_spv_del(os, a[i], n, depth-1);
			}

			ocs_free(os, a, SPV_ROWLEN*sizeof(*a));
		}
	}
}