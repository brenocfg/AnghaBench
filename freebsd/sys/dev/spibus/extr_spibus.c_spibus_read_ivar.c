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
typedef  int /*<<< orphan*/  uint32_t ;
struct spibus_ivar {int /*<<< orphan*/  clock; int /*<<< orphan*/  mode; int /*<<< orphan*/  cs; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct spibus_ivar* SPIBUS_IVAR (int /*<<< orphan*/ ) ; 
#define  SPIBUS_IVAR_CLOCK 130 
#define  SPIBUS_IVAR_CS 129 
#define  SPIBUS_IVAR_MODE 128 

__attribute__((used)) static int
spibus_read_ivar(device_t bus, device_t child, int which, uintptr_t *result)
{
	struct spibus_ivar *devi = SPIBUS_IVAR(child);

	switch (which) {
	default:
		return (EINVAL);
	case SPIBUS_IVAR_CS:
		*(uint32_t *)result = devi->cs;
		break;
	case SPIBUS_IVAR_MODE:
		*(uint32_t *)result = devi->mode;
		break;
	case SPIBUS_IVAR_CLOCK:
		*(uint32_t *)result = devi->clock;
		break;
	}
	return (0);
}