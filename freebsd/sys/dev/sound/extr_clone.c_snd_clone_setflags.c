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
typedef  int uint32_t ;
struct snd_clone {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_CLONE_ASSERT (int,char*) ; 
 int SND_CLONE_MASK ; 

uint32_t
snd_clone_setflags(struct snd_clone *c, uint32_t flags)
{
	SND_CLONE_ASSERT(c != NULL, ("NULL snd_clone"));
	SND_CLONE_ASSERT(!(flags & ~SND_CLONE_MASK),
	    ("invalid clone flags=0x%08x", flags));

	c->flags = flags;

	return (c->flags);
}