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
struct hdacc_softc {int /*<<< orphan*/ ** streams; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int HDAC_STREAM_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct hdacc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdacc_stream_alloc(device_t dev, device_t child, int dir, int format,
    int stripe, uint32_t **dmapos)
{
	struct hdacc_softc *codec = device_get_softc(dev);
	int stream;

	stream = HDAC_STREAM_ALLOC(device_get_parent(dev), dev,
	    dir, format, stripe, dmapos);
	if (stream > 0)
		codec->streams[dir][stream] = child;
	return (stream);
}