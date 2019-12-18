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
typedef  int grant_ref_t ;
typedef  int /*<<< orphan*/  domid_t ;

/* Variables and functions */
 scalar_t__ __predict_false (int) ; 
 int get_free_entries (int,int*) ; 
 int /*<<< orphan*/  gnttab_grant_foreign_transfer_ref (int,int /*<<< orphan*/ ,unsigned long) ; 

int
gnttab_grant_foreign_transfer(domid_t domid, unsigned long pfn,
    grant_ref_t *result)
{
	int error, ref;

	error = get_free_entries(1, &ref);
	if (__predict_false(error))
		return (error);

	gnttab_grant_foreign_transfer_ref(ref, domid, pfn);

	*result = ref;
	return (0);
}