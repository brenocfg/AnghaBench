#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  sm_lid; } ;
typedef  TYPE_1__ umad_port_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  sl; int /*<<< orphan*/  lid; } ;
typedef  TYPE_2__ ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int umad_get_port (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  umad_release_port (TYPE_1__*) ; 

int resolve_sm_portid(char *ca_name, uint8_t portnum, ib_portid_t *sm_id)
{
	umad_port_t port;
	int rc;

	if (!sm_id)
		return (-1);

	if ((rc = umad_get_port(ca_name, portnum, &port)) < 0)
		return rc;

	memset(sm_id, 0, sizeof(*sm_id));
	sm_id->lid = port.sm_lid;
	sm_id->sl = port.sm_sl;

	umad_release_port(&port);

	return 0;
}