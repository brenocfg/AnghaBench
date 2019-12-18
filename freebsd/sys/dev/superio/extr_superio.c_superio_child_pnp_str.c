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
typedef  int /*<<< orphan*/  superio_dev_type_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 char* devtype_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 int /*<<< orphan*/  superio_get_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
superio_child_pnp_str(device_t parent, device_t child, char *buf,
    size_t buflen)
{
	superio_dev_type_t type;

	type = superio_get_type(child);
	snprintf(buf, buflen, "type=%s", devtype_to_str(type));
	return (0);
}