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
struct iobus_devinfo {uintptr_t id_node; uintptr_t id_nregs; int /*<<< orphan*/  id_reg; int /*<<< orphan*/  id_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  IOBUS_IVAR_NAME 131 
#define  IOBUS_IVAR_NODE 130 
#define  IOBUS_IVAR_NREGS 129 
#define  IOBUS_IVAR_REGS 128 
 struct iobus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iobus_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
        struct iobus_devinfo *dinfo;

        if ((dinfo = device_get_ivars(child)) == NULL)
                return (ENOENT);

        switch (which) {
        case IOBUS_IVAR_NODE:
                *result = dinfo->id_node;
                break;
        case IOBUS_IVAR_NAME:
                *result = (uintptr_t)dinfo->id_name;
                break;
	case IOBUS_IVAR_NREGS:
		*result = dinfo->id_nregs;
		break;
	case IOBUS_IVAR_REGS:
		*result = (uintptr_t)dinfo->id_reg;
		break;
        default:
                return (ENOENT);
        }

        return (0);
}