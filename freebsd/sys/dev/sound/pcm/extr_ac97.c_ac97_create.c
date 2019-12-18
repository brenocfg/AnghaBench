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
struct ac97_info {int /*<<< orphan*/  flags; void* devinfo; int /*<<< orphan*/  dev; int /*<<< orphan*/  methods; int /*<<< orphan*/  name; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_F_EAPD_INV ; 
 int /*<<< orphan*/  M_AC97 ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int SD_F_SOFTPCMVOL ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ac97_info* malloc (int,int /*<<< orphan*/ ,int) ; 
 int pcm_getflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_setflags (int /*<<< orphan*/ ,int) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

struct ac97_info *
ac97_create(device_t dev, void *devinfo, kobj_class_t cls)
{
	struct ac97_info *codec;
	int i;

	codec = malloc(sizeof(*codec), M_AC97, M_WAITOK | M_ZERO);
	snprintf(codec->name, sizeof(codec->name), "%s:ac97",
	    device_get_nameunit(dev));
	codec->lock = snd_mtxcreate(codec->name, "ac97 codec");
	codec->methods = kobj_create(cls, M_AC97, M_WAITOK | M_ZERO);
	codec->dev = dev;
	codec->devinfo = devinfo;
	codec->flags = 0;

	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "eapdinv", &i) == 0 && i != 0)
		codec->flags |= AC97_F_EAPD_INV;

	if (resource_int_value(device_get_name(dev), device_get_unit(dev),
	    "softpcmvol", &i) == 0 && i != 0)
		pcm_setflags(dev, pcm_getflags(dev) | SD_F_SOFTPCMVOL);

	return codec;
}