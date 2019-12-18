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
struct isa_device {scalar_t__ id_vendorid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 
 char* pnp_eisaformat (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

__attribute__((used)) static int
isa_child_pnpinfo_str(device_t bus, device_t child, char *buf,
    size_t buflen)
{
	struct isa_device *idev = DEVTOISA(child);

	if (idev->id_vendorid)
		snprintf(buf, buflen, "pnpid=%s",
		    pnp_eisaformat(idev->id_vendorid));
	return (0);
}