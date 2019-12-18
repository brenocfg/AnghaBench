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
struct audio_params {int fd; int inited; int format; int channels; int rate; scalar_t__ dir; int /*<<< orphan*/  dev_name; } ;
struct audio {int fd; int inited; int format; int channels; int rate; scalar_t__ dir; int /*<<< orphan*/  dev_name; } ;
typedef  int audio_buf_info ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int /*<<< orphan*/  SNDCTL_DSP_CHANNELS ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETISPACE ; 
 int /*<<< orphan*/  SNDCTL_DSP_GETOSPACE ; 
 int /*<<< orphan*/  SNDCTL_DSP_RESET ; 
 int /*<<< orphan*/  SNDCTL_DSP_SETFMT ; 
 int /*<<< orphan*/  SNDCTL_DSP_SPEED ; 
 int /*<<< orphan*/  assert (struct audio_params*) ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 

int
audio_set_params(struct audio *aud, struct audio_params *params)
{
	int audio_fd;
	int format, channels, rate;
	int err;
#if DEBUG_HDA == 1
	audio_buf_info info;
#endif

	assert(aud);
	assert(params);

	if ((audio_fd = aud->fd) < 0) {
		DPRINTF("Incorrect audio device descriptor for %s\n",
		    aud->dev_name);
		return (-1);
	}

	/* Reset the device if it was previously opened */
	if (aud->inited) {
		err = ioctl(audio_fd, SNDCTL_DSP_RESET, NULL);
		if (err == -1) {
			DPRINTF("Failed to reset fd: %d, errno: %d\n",
			    aud->fd, errno);
			return (-1);
		}
	} else
		aud->inited = 1;

	/* Set the Format (Bits per Sample) */
	format = params->format;
	err = ioctl(audio_fd, SNDCTL_DSP_SETFMT, &format);
	if (err == -1) {
		DPRINTF("Fail to set fmt: 0x%x errno: %d\n",
		    params->format, errno);
		return -1;
	}

	/* The device does not support the requested audio format */
	if (format != params->format) {
		DPRINTF("Mismatch format: 0x%x params->format: 0x%x\n",
		    format, params->format);
		return -1;
	}

	/* Set the Number of Channels */
	channels = params->channels;
	err = ioctl(audio_fd, SNDCTL_DSP_CHANNELS, &channels);
	if (err == -1) {
		DPRINTF("Fail to set channels: %d errno: %d\n",
		    params->channels, errno);
		return -1;
	}

	/* The device does not support the requested no. of channels */
	if (channels != params->channels) {
		DPRINTF("Mismatch channels: %d params->channels: %d\n",
		    channels, params->channels);
		return -1;
	}

	/* Set the Sample Rate / Speed */
	rate = params->rate;
	err = ioctl(audio_fd, SNDCTL_DSP_SPEED, &rate);
	if (err == -1) {
		DPRINTF("Fail to set speed: %d errno: %d\n",
		    params->rate, errno);
		return -1;
	}

	/* The device does not support the requested rate / speed */
	if (rate != params->rate) {
		DPRINTF("Mismatch rate: %d params->rate: %d\n",
		    rate, params->rate);
		return -1;
	}

#if DEBUG_HDA == 1
	err = ioctl(audio_fd, aud->dir ? SNDCTL_DSP_GETOSPACE :
	    SNDCTL_DSP_GETISPACE, &info);
	if (err == -1) {
		DPRINTF("Fail to get audio buf info errno: %d\n", errno);
		return -1;
	}
	DPRINTF("fragstotal: 0x%x fragsize: 0x%x\n",
	    info.fragstotal, info.fragsize);
#endif
	return 0;
}