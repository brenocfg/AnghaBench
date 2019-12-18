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
struct snd_clone {int typemask; int maxunit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_CLONE_ASSERT (int,char*) ; 
 int SND_CLONE_MAXUNIT ; 

int
snd_clone_setmaxunit(struct snd_clone *c, int maxunit)
{
	SND_CLONE_ASSERT(c != NULL, ("NULL snd_clone"));
	SND_CLONE_ASSERT(maxunit == -1 ||
	    !(maxunit & ~(~c->typemask & SND_CLONE_MAXUNIT)),
	    ("maxunit overflow: typemask=0x%08x maxunit=%d",
	    c->typemask, maxunit));

	c->maxunit = (maxunit == -1) ? (~c->typemask & SND_CLONE_MAXUNIT) :
	    maxunit;

	return (c->maxunit);
}