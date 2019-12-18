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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int16_t ;
struct mrsas_softc {int max_fw_cmds; int /*<<< orphan*/ * req_desc; } ;
typedef  int /*<<< orphan*/  MRSAS_REQUEST_DESCRIPTOR_UNION ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

MRSAS_REQUEST_DESCRIPTOR_UNION *
mrsas_get_request_desc(struct mrsas_softc *sc, u_int16_t index)
{
	u_int8_t *p;

	KASSERT(index < sc->max_fw_cmds, ("req_desc is out of range"));
	p = sc->req_desc + sizeof(MRSAS_REQUEST_DESCRIPTOR_UNION) * index;

	return (MRSAS_REQUEST_DESCRIPTOR_UNION *) p;
}