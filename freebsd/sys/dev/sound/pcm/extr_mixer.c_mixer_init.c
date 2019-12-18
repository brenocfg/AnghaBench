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
typedef  int u_int16_t ;
struct snddev_info {int flags; struct cdev* mixer_dev; scalar_t__ eqpreamp; } ;
struct snd_mixer {int devs; int* realdev; int* parent; int* child; } ;
struct cdev {struct snd_mixer* si_drv1; } ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MIXER_TYPE_PRIMARY ; 
 int /*<<< orphan*/  PCMMINOR (int) ; 
 int SD_F_EQ ; 
 int SD_F_EQ_DEFAULT ; 
 int SD_F_EQ_MASK ; 
 int SD_F_SOFTPCMVOL ; 
 int /*<<< orphan*/  SND_DEV_CTL ; 
 int SOUND_MIXER_NRDEVICES ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct cdev* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  mixer_cdevsw ; 
 int /*<<< orphan*/  mixer_count ; 
 struct snd_mixer* mixer_obj_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixer_set (struct snd_mixer*,int,int) ; 
 int /*<<< orphan*/  mixer_setrecsrc (struct snd_mixer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int,char*,int*) ; 
 int* snd_mixerdefaults ; 
 char** snd_mixernames ; 
 int snd_mkunit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mixer_init(device_t dev, kobj_class_t cls, void *devinfo)
{
	struct snddev_info *snddev;
	struct snd_mixer *m;
	u_int16_t v;
	struct cdev *pdev;
	int i, unit, devunit, val;

	snddev = device_get_softc(dev);
	if (snddev == NULL)
		return (-1);

	if (resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "eq", &val) == 0 && val != 0) {
		snddev->flags |= SD_F_EQ;
		if ((val & SD_F_EQ_MASK) == val)
			snddev->flags |= val;
		else
			snddev->flags |= SD_F_EQ_DEFAULT;
		snddev->eqpreamp = 0;
	}

	m = mixer_obj_create(dev, cls, devinfo, MIXER_TYPE_PRIMARY, NULL);
	if (m == NULL)
		return (-1);

	for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
		v = snd_mixerdefaults[i];

		if (resource_int_value(device_get_name(dev),
		    device_get_unit(dev), snd_mixernames[i], &val) == 0) {
			if (val >= 0 && val <= 100) {
				v = (u_int16_t) val;
			}
		}

		mixer_set(m, i, v | (v << 8));
	}

	mixer_setrecsrc(m, 0); /* Set default input. */

	unit = device_get_unit(dev);
	devunit = snd_mkunit(unit, SND_DEV_CTL, 0);
	pdev = make_dev(&mixer_cdevsw, PCMMINOR(devunit),
		 UID_ROOT, GID_WHEEL, 0666, "mixer%d", unit);
	pdev->si_drv1 = m;
	snddev->mixer_dev = pdev;

	++mixer_count;

	if (bootverbose) {
		for (i = 0; i < SOUND_MIXER_NRDEVICES; i++) {
			if (!(m->devs & (1 << i)))
				continue;
			if (m->realdev[i] != i) {
				device_printf(dev, "Mixer \"%s\" -> \"%s\":",
				    snd_mixernames[i],
				    (m->realdev[i] < SOUND_MIXER_NRDEVICES) ?
				    snd_mixernames[m->realdev[i]] : "none");
			} else {
				device_printf(dev, "Mixer \"%s\":",
				    snd_mixernames[i]);
			}
			if (m->parent[i] < SOUND_MIXER_NRDEVICES)
				printf(" parent=\"%s\"",
				    snd_mixernames[m->parent[i]]);
			if (m->child[i] != 0)
				printf(" child=0x%08x", m->child[i]);
			printf("\n");
		}
		if (snddev->flags & SD_F_SOFTPCMVOL)
			device_printf(dev, "Soft PCM mixer ENABLED\n");
		if (snddev->flags & SD_F_EQ)
			device_printf(dev, "EQ Treble/Bass ENABLED\n");
	}

	return (0);
}