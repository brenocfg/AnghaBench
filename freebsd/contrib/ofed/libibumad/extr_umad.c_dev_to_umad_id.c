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
 int /*<<< orphan*/  DEBUG (char*,char const*,unsigned int,int) ; 
 int UMAD_CA_NAME_LEN ; 
 int UMAD_MAX_PORTS ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ umad_id_to_dev (int,char*,unsigned int*) ; 

__attribute__((used)) static int dev_to_umad_id(const char *dev, unsigned port)
{
	char umad_dev[UMAD_CA_NAME_LEN];
	unsigned umad_port;
	int id;

	for (id = 0; id < UMAD_MAX_PORTS; id++) {
		if (umad_id_to_dev(id, umad_dev, &umad_port) < 0)
			continue;
		if (strncmp(dev, umad_dev, UMAD_CA_NAME_LEN))
			continue;
		if (port != umad_port)
			continue;

		DEBUG("mapped %s %d to %d", dev, port, id);
		return id;
	}

	return -1;		/* not found */
}