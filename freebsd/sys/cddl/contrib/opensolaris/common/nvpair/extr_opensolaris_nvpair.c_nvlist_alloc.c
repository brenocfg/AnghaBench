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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int KM_SLEEP ; 
 int /*<<< orphan*/  nv_alloc_nosleep ; 
 int /*<<< orphan*/  nv_alloc_sleep ; 
 int nvlist_xalloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nvlist_alloc(nvlist_t **nvlp, uint_t nvflag, int kmflag)
{
#if defined(_KERNEL) && !defined(_BOOT)
	return (nvlist_xalloc(nvlp, nvflag,
	    (kmflag == KM_SLEEP ? nv_alloc_sleep : nv_alloc_nosleep)));
#else
	return (nvlist_xalloc(nvlp, nvflag, nv_alloc_nosleep));
#endif
}