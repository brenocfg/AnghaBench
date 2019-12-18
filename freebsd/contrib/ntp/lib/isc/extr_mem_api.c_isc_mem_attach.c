#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_mem_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* attach ) (TYPE_2__*,TYPE_2__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE (int) ; 
 int ISCAPI_MCTX_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,TYPE_2__**) ; 

void
isc_mem_attach(isc_mem_t *source, isc_mem_t **targetp) {
	REQUIRE(ISCAPI_MCTX_VALID(source));
	REQUIRE(targetp != NULL && *targetp == NULL);

	source->methods->attach(source, targetp);

	ENSURE(*targetp == source);
}