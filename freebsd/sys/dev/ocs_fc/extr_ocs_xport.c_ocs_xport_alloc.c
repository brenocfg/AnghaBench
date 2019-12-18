#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ocs; } ;
typedef  TYPE_1__ ocs_xport_t ;
typedef  int /*<<< orphan*/  ocs_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_M_ZERO ; 
 int /*<<< orphan*/  ocs_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ocs_malloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

ocs_xport_t *
ocs_xport_alloc(ocs_t *ocs)
{
	ocs_xport_t *xport;

	ocs_assert(ocs, NULL);
	xport = ocs_malloc(ocs, sizeof(*xport), OCS_M_ZERO);
	if (xport != NULL) {
		xport->ocs = ocs;
	}
	return xport;
}