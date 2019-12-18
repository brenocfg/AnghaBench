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
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  TRACE (char*,char const*,int) ; 
 char* UMAD_DEV_DIR ; 
 int dev_to_umad_id (char const*,int) ; 
 char* resolve_ca_name (char const*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

int umad_get_issm_path(const char *ca_name, int portnum, char path[], int max)
{
	int umad_id;

	TRACE("ca %s port %d", ca_name, portnum);

	if (!(ca_name = resolve_ca_name(ca_name, &portnum)))
		return -ENODEV;

	if ((umad_id = dev_to_umad_id(ca_name, portnum)) < 0)
		return -EINVAL;

	snprintf(path, max, "%s/issm%u", UMAD_DEV_DIR, umad_id);

	return 0;
}