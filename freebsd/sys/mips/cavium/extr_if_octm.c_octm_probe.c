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
typedef  int /*<<< orphan*/  device_t ;
typedef  int cvmx_mgmt_port_result_t ;

/* Variables and functions */
#define  CVMX_MGMT_PORT_INIT_ERROR 131 
#define  CVMX_MGMT_PORT_INVALID_PARAM 130 
#define  CVMX_MGMT_PORT_NO_MEMORY 129 
#define  CVMX_MGMT_PORT_SUCCESS 128 
 int EIO ; 
 int ENOBUFS ; 
 int ENXIO ; 
 int cvmx_mgmt_port_initialize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
octm_probe(device_t dev)
{
	cvmx_mgmt_port_result_t result;

	result = cvmx_mgmt_port_initialize(device_get_unit(dev));
	switch (result) {
	case CVMX_MGMT_PORT_SUCCESS:
		break;
	case CVMX_MGMT_PORT_NO_MEMORY:
		return (ENOBUFS);
	case CVMX_MGMT_PORT_INVALID_PARAM:
		return (ENXIO);
	case CVMX_MGMT_PORT_INIT_ERROR:
		return (EIO);
	}

	device_set_desc(dev, "Cavium Octeon Management Ethernet");

	return (0);
}