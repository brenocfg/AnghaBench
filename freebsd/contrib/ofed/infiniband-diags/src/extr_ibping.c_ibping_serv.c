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

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,...) ; 
 int IB_VENDOR_RANGE2_DATA_OFFS ; 
 int /*<<< orphan*/  IB_VENDOR_RANGE2_DATA_SIZE ; 
 int /*<<< orphan*/  host_and_domain ; 
 int /*<<< orphan*/  mad_free (void*) ; 
 void* mad_receive_via (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mad_respond_via (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 
 void* umad_get_mad (void*) ; 
 scalar_t__ umad_status (void*) ; 

__attribute__((used)) static char *ibping_serv(void)
{
	void *umad;
	void *mad;
	char *data;

	DEBUG("starting to serve...");

	while ((umad = mad_receive_via(0, -1, srcport))) {

		if (umad_status(umad) == 0) {
			mad = umad_get_mad(umad);
			data = (char *)mad + IB_VENDOR_RANGE2_DATA_OFFS;

			memcpy(data, host_and_domain, IB_VENDOR_RANGE2_DATA_SIZE);

			DEBUG("Pong: %s", data);

			if (mad_respond_via(umad, 0, 0, srcport) < 0)
				DEBUG("respond failed");

		}
		mad_free(umad);
	}

	DEBUG("server out");
	return 0;
}