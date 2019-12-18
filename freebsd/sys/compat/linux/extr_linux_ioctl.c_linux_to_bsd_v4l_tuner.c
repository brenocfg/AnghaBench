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
struct video_tuner {int /*<<< orphan*/  signal; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  name; int /*<<< orphan*/  tuner; } ;
struct l_video_tuner {int /*<<< orphan*/  signal; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  name; int /*<<< orphan*/  tuner; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_VIDEO_TUNER_NAME_SIZE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_to_bsd_v4l_tuner(struct l_video_tuner *lvt, struct video_tuner *vt)
{
	vt->tuner = lvt->tuner;
	strlcpy(vt->name, lvt->name, LINUX_VIDEO_TUNER_NAME_SIZE);
	vt->rangelow = lvt->rangelow;	/* possible long size conversion */
	vt->rangehigh = lvt->rangehigh;	/* possible long size conversion */
	vt->flags = lvt->flags;
	vt->mode = lvt->mode;
	vt->signal = lvt->signal;
	return (0);
}