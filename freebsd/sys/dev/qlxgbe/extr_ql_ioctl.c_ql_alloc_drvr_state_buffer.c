#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/ * drvr_state; } ;
struct TYPE_6__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_QLA83XXBUF ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_drvr_state_size (TYPE_2__*) ; 

void
ql_alloc_drvr_state_buffer(qla_host_t *ha)
{
	uint32_t drvr_state_size;

	drvr_state_size = ql_drvr_state_size(ha);

	ha->hw.drvr_state =  malloc(drvr_state_size, M_QLA83XXBUF, M_NOWAIT);	

	if (ha->hw.drvr_state != NULL)
		bzero(ha->hw.drvr_state, drvr_state_size);

	return;
}