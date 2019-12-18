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
struct timespec {int dummy; } ;
struct snd_clone_entry {struct timespec tsp; int /*<<< orphan*/ * parent; } ;
struct cdev {struct snd_clone_entry* si_drv2; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SND_CLONE_ASSERT (int /*<<< orphan*/ ,char*) ; 

int
snd_clone_getdevtime(struct cdev *dev, struct timespec *tsp)
{
	struct snd_clone_entry *ce;

	SND_CLONE_ASSERT(dev != NULL, ("NULL dev"));
	SND_CLONE_ASSERT(tsp != NULL, ("NULL timespec"));

	ce = dev->si_drv2;
	if (ce == NULL)
		return (ENODEV);

	SND_CLONE_ASSERT(ce->parent != NULL, ("NULL parent"));

	*tsp = ce->tsp;

	return (0);
}