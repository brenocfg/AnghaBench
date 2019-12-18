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
struct hdaa_devinfo {int /*<<< orphan*/  dev; } ;
struct hdaa_chan {int stripecap; scalar_t__ sid; scalar_t__ dir; int /*<<< orphan*/  flags; int /*<<< orphan*/  blkcnt; int /*<<< orphan*/  blksz; int /*<<< orphan*/  b; int /*<<< orphan*/  dmapos; scalar_t__ stripectl; struct hdaa_devinfo* devinfo; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  HDAA_CHN_RUNNING ; 
 scalar_t__ HDAC_STREAM_ALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HDAC_STREAM_RESET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  HDAC_STREAM_START (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCMDIR_PLAY ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ fls (int) ; 
 int hda_get_stripes_mask (int /*<<< orphan*/ ) ; 
 int hdaa_allowed_stripes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_audio_setup (struct hdaa_chan*) ; 
 int /*<<< orphan*/  hdaa_stream_format (struct hdaa_chan*) ; 
 int /*<<< orphan*/  sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdaa_channel_start(struct hdaa_chan *ch)
{
	struct hdaa_devinfo *devinfo = ch->devinfo;
	uint32_t fmt;

	fmt = hdaa_stream_format(ch);
	ch->stripectl = fls(ch->stripecap & hdaa_allowed_stripes(fmt) &
	    hda_get_stripes_mask(devinfo->dev)) - 1;
	ch->sid = HDAC_STREAM_ALLOC(device_get_parent(devinfo->dev), devinfo->dev,
	    ch->dir == PCMDIR_PLAY ? 1 : 0, fmt, ch->stripectl, &ch->dmapos);
	if (ch->sid <= 0)
		return (EBUSY);
	hdaa_audio_setup(ch);
	HDAC_STREAM_RESET(device_get_parent(devinfo->dev), devinfo->dev,
	    ch->dir == PCMDIR_PLAY ? 1 : 0, ch->sid);
	HDAC_STREAM_START(device_get_parent(devinfo->dev), devinfo->dev,
	    ch->dir == PCMDIR_PLAY ? 1 : 0, ch->sid,
	    sndbuf_getbufaddr(ch->b), ch->blksz, ch->blkcnt);
	ch->flags |= HDAA_CHN_RUNNING;
	return (0);
}