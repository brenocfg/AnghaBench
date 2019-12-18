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
struct aac_softc {int flags; } ;
struct TYPE_3__ {int largeLBA; int JBODSupport; } ;
struct TYPE_4__ {scalar_t__ fValue; TYPE_1__ fBits; } ;
struct aac_features {TYPE_2__ feat; } ;
typedef  int /*<<< orphan*/  f ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int AAC_FLAGS_LBA_64BIT ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int copyin (int /*<<< orphan*/ ,struct aac_features*,int) ; 
 int copyout (struct aac_features*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

__attribute__((used)) static int
aac_supported_features(struct aac_softc *sc, caddr_t uptr)
{
	struct aac_features f;
	int error;

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	if ((error = copyin(uptr, &f, sizeof (f))) != 0)
		return (error);

	/*
	 * When the management driver receives FSACTL_GET_FEATURES ioctl with
	 * ALL zero in the featuresState, the driver will return the current
	 * state of all the supported features, the data field will not be
	 * valid.
	 * When the management driver receives FSACTL_GET_FEATURES ioctl with
	 * a specific bit set in the featuresState, the driver will return the
	 * current state of this specific feature and whatever data that are
	 * associated with the feature in the data field or perform whatever
	 * action needed indicates in the data field.
	 */
	 if (f.feat.fValue == 0) {
		f.feat.fBits.largeLBA =
		    (sc->flags & AAC_FLAGS_LBA_64BIT) ? 1 : 0;
		f.feat.fBits.JBODSupport = 1;
		/* TODO: In the future, add other features state here as well */
	} else {
		if (f.feat.fBits.largeLBA)
			f.feat.fBits.largeLBA =
			    (sc->flags & AAC_FLAGS_LBA_64BIT) ? 1 : 0;
		/* TODO: Add other features state and data in the future */
	}

	error = copyout(&f, uptr, sizeof (f));
	return (error);
}