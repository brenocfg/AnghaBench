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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_UNSOL_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 struct hdacc_softc* device_get_softc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hdacc_unsol_alloc(device_t dev, device_t child, int wanted)
{
	struct hdacc_softc *codec = device_get_softc(dev);
	int tag;

	wanted &= 0x3f;
	tag = wanted;
	do {
		if (codec->tags[tag] == NULL) {
			codec->tags[tag] = child;
			HDAC_UNSOL_ALLOC(device_get_parent(dev), dev, tag);
			return (tag);
		}
		tag++;
		tag &= 0x3f;
	} while (tag != wanted);
	return (-1);
}