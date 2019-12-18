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
struct snd_mixer {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_class_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIXER_TYPE_SECONDARY ; 
 int /*<<< orphan*/  mixer_count ; 
 struct snd_mixer* mixer_obj_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,char const*) ; 

struct snd_mixer *
mixer_create(device_t dev, kobj_class_t cls, void *devinfo, const char *desc)
{
	struct snd_mixer *m;

	m = mixer_obj_create(dev, cls, devinfo, MIXER_TYPE_SECONDARY, desc);

	if (m != NULL)
		++mixer_count;

	return (m);
}