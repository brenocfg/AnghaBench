#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aac_cam {TYPE_1__* inf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  aac_sc; } ;

/* Variables and functions */
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
aac_cam_probe(device_t dev)
{
	struct aac_cam *camsc;

	camsc = (struct aac_cam *)device_get_softc(dev);
	if (!camsc->inf)
		return (0);
	fwprintf(camsc->inf->aac_sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");
	return (0);
}