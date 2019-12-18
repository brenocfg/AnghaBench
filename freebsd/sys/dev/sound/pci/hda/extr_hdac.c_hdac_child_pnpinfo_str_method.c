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
struct hdac_softc {TYPE_1__* codecs; } ;
typedef  size_t nid_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int vendor_id; int device_id; int revision_id; int stepping_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 struct hdac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,int,int) ; 

__attribute__((used)) static int
hdac_child_pnpinfo_str_method(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	struct hdac_softc *sc = device_get_softc(dev);
	nid_t cad = (uintptr_t)device_get_ivars(child);

	snprintf(buf, buflen, "vendor=0x%04x device=0x%04x revision=0x%02x "
	    "stepping=0x%02x",
	    sc->codecs[cad].vendor_id, sc->codecs[cad].device_id,
	    sc->codecs[cad].revision_id, sc->codecs[cad].stepping_id);
	return (0);
}