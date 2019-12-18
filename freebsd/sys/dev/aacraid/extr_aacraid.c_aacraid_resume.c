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
struct aac_softc {int /*<<< orphan*/  aac_state; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_ACCESS_DEVREG (struct aac_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAC_ENABLE_INTERRUPT ; 
 int /*<<< orphan*/  AAC_STATE_SUSPEND ; 
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 struct aac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

int
aacraid_resume(device_t dev)
{
	struct aac_softc *sc;

	sc = device_get_softc(dev);

	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	sc->aac_state &= ~AAC_STATE_SUSPEND;
	AAC_ACCESS_DEVREG(sc, AAC_ENABLE_INTERRUPT);
	return(0);
}