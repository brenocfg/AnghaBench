#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct tuple_callbacks {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nid; } ;
struct TYPE_4__ {TYPE_1__ lan; } ;
struct cardbus_devinfo {int funcid; int fepresent; TYPE_2__ funce; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  PCCARD_FUNCTION_NETWORK 129 
#define  PCCARD_TPLFE_TYPE_LAN_NID 128 
 int /*<<< orphan*/  bcopy (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cardbus_cis_debug ; 
 struct cardbus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
decode_tuple_funce(device_t cbdev, device_t child, int id,
    int len, uint8_t *tupledata, uint32_t start, uint32_t *off,
    struct tuple_callbacks *info, void *argp)
{
	struct cardbus_devinfo *dinfo = device_get_ivars(child);
	int type, i;

	if (cardbus_cis_debug) {
		printf("Function Extension: ");
		for (i = 0; i < len; i++)
			printf("%02x", tupledata[i]);
		printf("\n");
	}
	if (len < 2)			/* too short */
		return (0);
	type = tupledata[0];		/* XXX <32 always? */
	switch (dinfo->funcid) {
	case PCCARD_FUNCTION_NETWORK:
		switch (type) {
		case PCCARD_TPLFE_TYPE_LAN_NID:
			if (tupledata[1] > sizeof(dinfo->funce.lan.nid)) {
				/* ignore, warning? */
				return (0);
			}
			bcopy(tupledata + 2, dinfo->funce.lan.nid,
			    tupledata[1]);
			break;
		}
		dinfo->fepresent |= 1<<type;
		break;
	}
	return (0);
}