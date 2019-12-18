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
 int ENOENT ; 
#define  LEGACY_IVAR_PCIBUS 131 
#define  LEGACY_IVAR_PCIDOMAIN 130 
#define  LEGACY_IVAR_PCIFUNC 129 
#define  LEGACY_IVAR_PCISLOT 128 

__attribute__((used)) static int
legacy_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct legacy_device *atdev = DEVTOAT(child);

	switch (which) {
	case LEGACY_IVAR_PCIDOMAIN:
		*result = 0;
		break;
	case LEGACY_IVAR_PCIBUS:
		*result = atdev->lg_pcibus;
		break;
	case LEGACY_IVAR_PCISLOT:
		*result = atdev->lg_pcislot;
		break;
	case LEGACY_IVAR_PCIFUNC:
		*result = atdev->lg_pcifunc;
		break;
	default:
		return ENOENT;
	}
	return 0;
}