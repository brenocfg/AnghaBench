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
struct snddev_info {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCMUNIT (struct cdev*) ; 
 struct snddev_info* devclass_get_softc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_devclass ; 

__attribute__((used)) static struct snddev_info *
dsp_get_info(struct cdev *dev)
{
	return (devclass_get_softc(pcm_devclass, PCMUNIT(dev)));
}