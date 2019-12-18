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
typedef  int u_int8_t ;
struct mrsas_ident {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 char* MRSAS_VERSION ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mrsas_ident* mrsas_find_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
mrsas_probe(device_t dev)
{
	static u_int8_t first_ctrl = 1;
	struct mrsas_ident *id;

	if ((id = mrsas_find_ident(dev)) != NULL) {
		if (first_ctrl) {
			printf("AVAGO MegaRAID SAS FreeBSD mrsas driver version: %s\n",
			    MRSAS_VERSION);
			first_ctrl = 0;
		}
		device_set_desc(dev, id->desc);
		/* between BUS_PROBE_DEFAULT and BUS_PROBE_LOW_PRIORITY */
		return (-30);
	}
	return (ENXIO);
}