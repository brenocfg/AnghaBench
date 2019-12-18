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
struct snd_clone_entry {int flags; scalar_t__ unit; struct cdev* devt; int /*<<< orphan*/ * parent; } ;
struct cdev {struct snd_clone_entry* si_drv2; } ;

/* Variables and functions */
 int SND_CLONE_ALLOC ; 
 int /*<<< orphan*/  SND_CLONE_ASSERT (int,char*) ; 
 int SND_CLONE_INVOKE ; 
 scalar_t__ dev2unit (struct cdev*) ; 

void
snd_clone_register(struct snd_clone_entry *ce, struct cdev *dev)
{
	SND_CLONE_ASSERT(ce != NULL, ("NULL snd_clone_entry"));
	SND_CLONE_ASSERT(dev != NULL, ("NULL dev"));
	SND_CLONE_ASSERT(dev->si_drv2 == NULL, ("dev->si_drv2 not NULL"));
	SND_CLONE_ASSERT((ce->flags & SND_CLONE_ALLOC) == SND_CLONE_ALLOC,
	    ("invalid clone alloc flags=0x%08x", ce->flags));
	SND_CLONE_ASSERT(ce->devt == NULL, ("ce->devt not NULL"));
	SND_CLONE_ASSERT(ce->unit == dev2unit(dev),
	    ("invalid unit ce->unit=0x%08x dev2unit=0x%08x",
	    ce->unit, dev2unit(dev)));

	SND_CLONE_ASSERT(ce->parent != NULL, ("NULL parent"));

	dev->si_drv2 = ce;
	ce->devt = dev;
	ce->flags &= ~SND_CLONE_ALLOC;
	ce->flags |= SND_CLONE_INVOKE;
}