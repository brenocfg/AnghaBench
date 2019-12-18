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
typedef  int uint32_t ;
struct hdaa_devinfo {int /*<<< orphan*/  dev; } ;
struct hdaa_chan {int* dmapos; scalar_t__ dir; int blksz; int blkcnt; int /*<<< orphan*/  sid; struct hdaa_devinfo* devinfo; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int HDAC_STREAM_GETPTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int HDA_BLK_ALIGN ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_lock (struct hdaa_devinfo*) ; 
 int /*<<< orphan*/  hdaa_unlock (struct hdaa_devinfo*) ; 

__attribute__((used)) static uint32_t
hdaa_channel_getptr(kobj_t obj, void *data)
{
	struct hdaa_chan *ch = data;
	struct hdaa_devinfo *devinfo = ch->devinfo;
	uint32_t ptr;

	hdaa_lock(devinfo);
	if (ch->dmapos != NULL) {
		ptr = *(ch->dmapos);
	} else {
		ptr = HDAC_STREAM_GETPTR(
		    device_get_parent(devinfo->dev), devinfo->dev,
		    ch->dir == PCMDIR_PLAY ? 1 : 0, ch->sid);
	}
	hdaa_unlock(devinfo);

	/*
	 * Round to available space and force 128 bytes aligment.
	 */
	ptr %= ch->blksz * ch->blkcnt;
	ptr &= HDA_BLK_ALIGN;

	return (ptr);
}