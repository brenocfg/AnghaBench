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
struct hdaa_chan {int /*<<< orphan*/  devinfo; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  PCMTRIG_ABORT 130 
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
#define  PCMTRIG_START 129 
#define  PCMTRIG_STOP 128 
 int hdaa_channel_start (struct hdaa_chan*) ; 
 int /*<<< orphan*/  hdaa_channel_stop (struct hdaa_chan*) ; 
 int /*<<< orphan*/  hdaa_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hdaa_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdaa_channel_trigger(kobj_t obj, void *data, int go)
{
	struct hdaa_chan *ch = data;
	int error = 0;

	if (!PCMTRIG_COMMON(go))
		return (0);

	hdaa_lock(ch->devinfo);
	switch (go) {
	case PCMTRIG_START:
		error = hdaa_channel_start(ch);
		break;
	case PCMTRIG_STOP:
	case PCMTRIG_ABORT:
		hdaa_channel_stop(ch);
		break;
	default:
		break;
	}
	hdaa_unlock(ch->devinfo);

	return (error);
}