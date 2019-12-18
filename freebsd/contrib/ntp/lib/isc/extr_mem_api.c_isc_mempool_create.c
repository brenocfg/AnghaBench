#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_mempool_t ;
struct TYPE_7__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_mem_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* mpcreate ) (TYPE_2__*,size_t,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISCAPI_MCTX_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int /*<<< orphan*/ **) ; 

isc_result_t
isc_mempool_create(isc_mem_t *mctx, size_t size, isc_mempool_t **mpctxp) {
	REQUIRE(ISCAPI_MCTX_VALID(mctx));

	return (mctx->methods->mpcreate(mctx, size, mpctxp));
}