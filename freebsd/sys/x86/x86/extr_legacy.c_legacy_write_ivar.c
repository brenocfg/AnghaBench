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
struct legacy_device {uintptr_t lg_pcibus; uintptr_t lg_pcislot; uintptr_t lg_pcifunc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct legacy_device* DEVTOAT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
#define  LEGACY_IVAR_PCIBUS 131 
#define  LEGACY_IVAR_PCIDOMAIN 130 
#define  LEGACY_IVAR_PCIFUNC 129 
#define  LEGACY_IVAR_PCISLOT 128 

__attribute__((used)) static int
legacy_write_ivar(device_t dev, device_t child, int which, uintptr_t value)
{
	struct legacy_device *atdev = DEVTOAT(child);

	switch (which) {
	case LEGACY_IVAR_PCIDOMAIN:
		return EINVAL;
	case LEGACY_IVAR_PCIBUS:
		atdev->lg_pcibus = value;
		break;
	case LEGACY_IVAR_PCISLOT:
		atdev->lg_pcislot = value;
		break;
	case LEGACY_IVAR_PCIFUNC:
		atdev->lg_pcifunc = value;
		break;
	default:
		return ENOENT;
	}
	return 0;
}