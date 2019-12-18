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
struct snd_mixer {int hwvol_step; int /*<<< orphan*/  hwvol_mixer; } ;
struct cdev {struct snd_mixer* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SOUND_MIXER_VOLUME ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct snd_mixer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 struct cdev* mixer_get_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_hw_snd_hwvol_mixer ; 

int
mixer_hwvol_init(device_t dev)
{
	struct snd_mixer *m;
	struct cdev *pdev;

	pdev = mixer_get_devt(dev);
	m = pdev->si_drv1;

	m->hwvol_mixer = SOUND_MIXER_VOLUME;
	m->hwvol_step = 5;
	SYSCTL_ADD_INT(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
            OID_AUTO, "hwvol_step", CTLFLAG_RWTUN, &m->hwvol_step, 0, "");
	SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
	    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
            OID_AUTO, "hwvol_mixer", CTLTYPE_STRING | CTLFLAG_RWTUN, m, 0,
	    sysctl_hw_snd_hwvol_mixer, "A", "");
	return 0;
}