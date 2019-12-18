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
struct snd_clone {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SND_CLONE_ASSERT (int /*<<< orphan*/ ,char*) ; 
 int SND_CLONE_ENABLE ; 

int
snd_clone_enable(struct snd_clone *c)
{
	SND_CLONE_ASSERT(c != NULL, ("NULL snd_clone"));

	if (c->flags & SND_CLONE_ENABLE)
		return (EINVAL);

	c->flags |= SND_CLONE_ENABLE;

	return (0);
}