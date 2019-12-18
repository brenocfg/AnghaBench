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
typedef  int /*<<< orphan*/  uint32_t ;
struct hdac_softc {int /*<<< orphan*/  mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_READ_4 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ HDAC_SDLPIB ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct hdac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hdac_find_stream (struct hdac_softc*,int,int) ; 

__attribute__((used)) static uint32_t
hdac_stream_getptr(device_t dev, device_t child, int dir, int stream)
{
	struct hdac_softc *sc = device_get_softc(dev);
	int ss, off;

	ss = hdac_find_stream(sc, dir, stream);
	KASSERT(ss >= 0,
	    ("Reset for not allocated stream (%d/%d)\n", dir, stream));

	off = ss << 5;
	return (HDAC_READ_4(&sc->mem, off + HDAC_SDLPIB));
}