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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
#define  PCIB_IVAR_BUS 129 
#define  PCIB_IVAR_DOMAIN 128 
 int /*<<< orphan*/  legacy_set_pcibus (int /*<<< orphan*/ ,uintptr_t) ; 

int
legacy_pcib_write_ivar(device_t dev, device_t child, int which,
    uintptr_t value)
{

	switch (which) {
	case  PCIB_IVAR_DOMAIN:
		return EINVAL;
	case  PCIB_IVAR_BUS:
		legacy_set_pcibus(dev, value);
		return 0;
	}
	return ENOENT;
}