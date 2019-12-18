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
struct hdacc_softc {int /*<<< orphan*/ ** tags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_UNSOL_FREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct hdacc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdacc_unsol_free(device_t dev, device_t child, int tag)
{
	struct hdacc_softc *codec = device_get_softc(dev);

	KASSERT(tag >= 0 && tag <= 0x3f, ("Wrong tag value %d\n", tag));
	codec->tags[tag] = NULL;
	HDAC_UNSOL_FREE(device_get_parent(dev), dev, tag);
}