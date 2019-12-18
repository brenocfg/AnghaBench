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
struct mii_data {int /*<<< orphan*/  mii_media_active; int /*<<< orphan*/  mii_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIIBUS_STATCHG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setbaudrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_baudrate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
miibus_statchg(device_t dev)
{
	device_t		parent;
	struct mii_data		*mii;

	parent = device_get_parent(dev);
	MIIBUS_STATCHG(parent);

	mii = device_get_softc(dev);
	if_setbaudrate(mii->mii_ifp, ifmedia_baudrate(mii->mii_media_active));
}