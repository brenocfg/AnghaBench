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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_5__ {scalar_t__ family; int bitlen; int /*<<< orphan*/  refcount; int /*<<< orphan*/  add; } ;
typedef  TYPE_1__ isc_prefix_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  _new_prefix (int /*<<< orphan*/ *,TYPE_1__**,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ isc_refcount_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_refcount_increment (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static isc_result_t
_ref_prefix(isc_mem_t *mctx, isc_prefix_t **target, isc_prefix_t *prefix) {
	INSIST(prefix != NULL);
	INSIST((prefix->family == AF_INET && prefix->bitlen <= 32) ||
	       (prefix->family == AF_INET6 && prefix->bitlen <= 128) ||
	       (prefix->family == AF_UNSPEC && prefix->bitlen == 0));
	REQUIRE(target != NULL && *target == NULL);

	/*
	 * If this prefix is a static allocation, copy it into new memory.
	 * (Note, the refcount still has to be destroyed by the calling
	 * routine.)
	 */
	if (isc_refcount_current(&prefix->refcount) == 0) {
		isc_result_t ret;
		ret = _new_prefix(mctx, target, prefix->family,
				  &prefix->add, prefix->bitlen);
		return ret;
	}

	isc_refcount_increment(&prefix->refcount, NULL);

	*target = prefix;
	return (ISC_R_SUCCESS);
}