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
struct snd_clone_entry {int flags; int pid; int /*<<< orphan*/ * parent; } ;
struct cdev {struct snd_clone_entry* si_drv2; } ;

/* Variables and functions */
 int EBADF ; 
 int ENODEV ; 
 int /*<<< orphan*/  SND_CLONE_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int SND_CLONE_BUSY ; 
 int SND_CLONE_INVOKE ; 

int
snd_clone_release(struct cdev *dev)
{
	struct snd_clone_entry *ce;

	SND_CLONE_ASSERT(dev != NULL, ("NULL dev"));

	ce = dev->si_drv2;
	if (ce == NULL)
		return (ENODEV);

	SND_CLONE_ASSERT(ce->parent != NULL, ("NULL parent"));

	ce->flags &= ~SND_CLONE_INVOKE;

	if (!(ce->flags & SND_CLONE_BUSY))
		return (EBADF);

	ce->flags &= ~SND_CLONE_BUSY;
	ce->pid = -1;

	return (0);
}