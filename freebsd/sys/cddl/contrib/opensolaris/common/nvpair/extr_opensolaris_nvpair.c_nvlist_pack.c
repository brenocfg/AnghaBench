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
 int nvlist_xpack (int /*<<< orphan*/ *,char**,size_t*,int,int /*<<< orphan*/ ) ; 

int
nvlist_pack(nvlist_t *nvl, char **bufp, size_t *buflen, int encoding,
    int kmflag)
{
#if defined(_KERNEL) && !defined(_BOOT)
	return (nvlist_xpack(nvl, bufp, buflen, encoding,
	    (kmflag == KM_SLEEP ? nv_alloc_sleep : nv_alloc_nosleep)));
#else
	return (nvlist_xpack(nvl, bufp, buflen, encoding, nv_alloc_nosleep));
#endif
}