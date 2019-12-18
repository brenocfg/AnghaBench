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
struct TYPE_7__ {TYPE_1__* methods; } ;
typedef  TYPE_2__ isc_appctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* ctxdestroy ) (TYPE_2__**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENSURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ISCAPI_APPCTX_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**) ; 

void
isc_appctx_destroy(isc_appctx_t **ctxp) {
	REQUIRE(ctxp != NULL && ISCAPI_APPCTX_VALID(*ctxp));

	(*ctxp)->methods->ctxdestroy(ctxp);

	ENSURE(*ctxp == NULL);
}