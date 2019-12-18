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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int pmap_pkru_assign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pmap_pkru_check_uargs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_pkru_update_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

int
pmap_pkru_set(pmap_t pmap, vm_offset_t sva, vm_offset_t eva, u_int keyidx,
    int flags)
{
	int error;

	sva = trunc_page(sva);
	eva = round_page(eva);
	error = pmap_pkru_check_uargs(pmap, sva, eva, keyidx, flags);
	if (error != 0)
		return (error);
	for (;;) {
		PMAP_LOCK(pmap);
		error = pmap_pkru_assign(pmap, sva, eva, keyidx, flags);
		if (error == 0)
			pmap_pkru_update_range(pmap, sva, eva, keyidx);
		PMAP_UNLOCK(pmap);
		if (error != ENOMEM)
			break;
		vm_wait(NULL);
	}
	return (error);
}