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
typedef  int /*<<< orphan*/  isc_boolean_t ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portset_isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

isc_boolean_t
isc_portset_isset(isc_portset_t *portset, in_port_t port) {
	REQUIRE(portset != NULL);

	return (portset_isset(portset, port));
}