#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/ * drvr_state; } ;
struct TYPE_9__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;
struct TYPE_10__ {scalar_t__ size; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_3__ qla_driver_state_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,scalar_t__) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ql_capture_drvr_state (TYPE_2__*) ; 
 scalar_t__ ql_drvr_state_size (TYPE_2__*) ; 

__attribute__((used)) static int
ql_drvr_state(qla_host_t *ha, qla_driver_state_t *state)
{
	int rval = 0;
	uint32_t drvr_state_size;

	drvr_state_size = ql_drvr_state_size(ha);

	if (state->buffer == NULL) {
		state->size = drvr_state_size;
		return (0);
	}
		
	if (state->size < drvr_state_size)
		return (ENXIO);

	if (ha->hw.drvr_state == NULL)
		return (ENOMEM);

	ql_capture_drvr_state(ha);

	rval = copyout(ha->hw.drvr_state, state->buffer, drvr_state_size);

	bzero(ha->hw.drvr_state, drvr_state_size);

	return (rval);
}