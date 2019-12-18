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
struct ucred {int dummy; } ;
struct snddev_info {struct cdev* mixer_dev; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCM_REGISTERED (struct snddev_info*) ; 
 int /*<<< orphan*/  dev_ref (struct cdev*) ; 
 struct snddev_info* devclass_get_softc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_devclass ; 
 int /*<<< orphan*/  snd_unit ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
mixer_clone(void *arg,
    struct ucred *cred,
    char *name, int namelen, struct cdev **dev)
{
	struct snddev_info *d;

	if (*dev != NULL)
		return;
	if (strcmp(name, "mixer") == 0) {
		d = devclass_get_softc(pcm_devclass, snd_unit);
		if (PCM_REGISTERED(d) && d->mixer_dev != NULL) {
			*dev = d->mixer_dev;
			dev_ref(*dev);
		}
	}
}