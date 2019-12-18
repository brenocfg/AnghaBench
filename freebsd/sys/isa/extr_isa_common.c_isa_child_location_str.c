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
struct isa_device {int id_pnphandle; scalar_t__ id_vendorid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static int
isa_child_location_str(device_t bus, device_t child, char *buf,
    size_t buflen)
{
#if 0
	/* id_pnphandle isn't there yet */
	struct isa_device *idev = DEVTOISA(child);

	if (idev->id_vendorid)
		snprintf(buf, buflen, "pnphandle=%d", idev->id_pnphandle);
#endif
	/* Nothing here yet */
	*buf = '\0';
	return (0);
}