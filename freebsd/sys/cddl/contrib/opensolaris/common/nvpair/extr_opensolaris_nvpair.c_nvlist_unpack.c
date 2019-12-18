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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int KM_SLEEP ; 
 int /*<<< orphan*/  nv_alloc_nosleep ; 
 int /*<<< orphan*/  nv_alloc_sleep ; 
 int nvlist_xunpack (char*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int
nvlist_unpack(char *buf, size_t buflen, nvlist_t **nvlp, int kmflag)
{
#if defined(_KERNEL) && !defined(_BOOT)
	return (nvlist_xunpack(buf, buflen, nvlp,
	    (kmflag == KM_SLEEP ? nv_alloc_sleep : nv_alloc_nosleep)));
#else
	return (nvlist_xunpack(buf, buflen, nvlp, nv_alloc_nosleep));
#endif
}