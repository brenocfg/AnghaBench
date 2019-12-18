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
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
typedef  int /*<<< orphan*/  isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUNTIME_CHECK (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createlock ; 
 int /*<<< orphan*/ * hash ; 
 int /*<<< orphan*/  initialize_lock ; 
 scalar_t__ isc_hash_ctxcreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **) ; 
 scalar_t__ isc_once_do (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  once ; 

isc_result_t
isc_hash_create(isc_mem_t *mctx, isc_entropy_t *entropy, size_t limit) {
	isc_result_t result = ISC_R_SUCCESS;

	REQUIRE(mctx != NULL);
	INSIST(hash == NULL);

	RUNTIME_CHECK(isc_once_do(&once, initialize_lock) == ISC_R_SUCCESS);

	LOCK(&createlock);

	if (hash == NULL)
		result = isc_hash_ctxcreate(mctx, entropy, limit, &hash);

	UNLOCK(&createlock);

	return (result);
}