#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_5__ {scalar_t__ dn_maxblkid; } ;
typedef  TYPE_1__ dnode_t ;

/* Variables and functions */
 scalar_t__ DMU_OBJECT_END ; 
 int /*<<< orphan*/  FTAG ; 
 int dmu_free_long_range_impl (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,scalar_t__) ; 
 int dnode_hold (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  dnode_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
dmu_free_long_range(objset_t *os, uint64_t object,
    uint64_t offset, uint64_t length)
{
	dnode_t *dn;
	int err;

	err = dnode_hold(os, object, FTAG, &dn);
	if (err != 0)
		return (err);
	err = dmu_free_long_range_impl(os, dn, offset, length);

	/*
	 * It is important to zero out the maxblkid when freeing the entire
	 * file, so that (a) subsequent calls to dmu_free_long_range_impl()
	 * will take the fast path, and (b) dnode_reallocate() can verify
	 * that the entire file has been freed.
	 */
	if (err == 0 && offset == 0 && length == DMU_OBJECT_END)
		dn->dn_maxblkid = 0;

	dnode_rele(dn, FTAG);
	return (err);
}