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
struct uncached_pool {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int PAL_VISIBILITY_OK ; 
 int PAL_VISIBILITY_OK_REMOTE_NEEDED ; 
 int /*<<< orphan*/  PAL_VISIBILITY_PHYSICAL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int ia64_pal_prefetch_visibility (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uncached_ipi_visibility(void *data)
{
	int status;
	struct uncached_pool *uc_pool = (struct uncached_pool *)data;

	status = ia64_pal_prefetch_visibility(PAL_VISIBILITY_PHYSICAL);
	if ((status != PAL_VISIBILITY_OK) &&
	    (status != PAL_VISIBILITY_OK_REMOTE_NEEDED))
		atomic_inc(&uc_pool->status);
}