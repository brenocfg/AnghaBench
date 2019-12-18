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
typedef  int /*<<< orphan*/  isc_portset_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
isc_portset_destroy(isc_mem_t *mctx, isc_portset_t **portsetp) {
	isc_portset_t *portset;

	REQUIRE(portsetp != NULL);
	portset = *portsetp;

	isc_mem_put(mctx, portset, sizeof(*portset));
}