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
bsd_to_linux_v4l_tuner(struct video_tuner *vt, struct l_video_tuner *lvt)
{
	lvt->tuner = vt->tuner;
	strlcpy(lvt->name, vt->name, LINUX_VIDEO_TUNER_NAME_SIZE);
	lvt->rangelow = vt->rangelow;	/* possible long size conversion */
	lvt->rangehigh = vt->rangehigh;	/* possible long size conversion */
	lvt->flags = vt->flags;
	lvt->mode = vt->mode;
	lvt->signal = vt->signal;
	return (0);
}