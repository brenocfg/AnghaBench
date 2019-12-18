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
struct snd_clone_entry {struct snd_clone* parent; } ;
struct snd_clone {scalar_t__ refcount; int flags; } ;
struct cdev {struct snd_clone_entry* si_drv2; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_CLONE_ASSERT (int,char*) ; 
 int SND_CLONE_GC_LASTREF ; 
 int SND_CLONE_GC_UNREF ; 
 int /*<<< orphan*/  snd_clone_gc (struct snd_clone*) ; 

int
snd_clone_unref(struct cdev *dev)
{
	struct snd_clone_entry *ce;
	struct snd_clone *c;

	SND_CLONE_ASSERT(dev != NULL, ("NULL dev"));

	ce = dev->si_drv2;
	if (ce == NULL)
		return (0);

	c = ce->parent;
	SND_CLONE_ASSERT(c != NULL, ("NULL parent"));
	SND_CLONE_ASSERT(c->refcount > 0, ("refcount <= 0"));

	c->refcount--;

	/* 
	 * Run automatic garbage collector, if needed.
	 */
	if ((c->flags & SND_CLONE_GC_UNREF) &&
	    (!(c->flags & SND_CLONE_GC_LASTREF) ||
	    (c->refcount == 0 && (c->flags & SND_CLONE_GC_LASTREF))))
		(void)snd_clone_gc(c);

	return (c->refcount);
}