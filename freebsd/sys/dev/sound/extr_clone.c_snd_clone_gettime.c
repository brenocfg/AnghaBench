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
struct snd_clone {struct timespec tsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_CLONE_ASSERT (int /*<<< orphan*/ ,char*) ; 

int
snd_clone_gettime(struct snd_clone *c, struct timespec *tsp)
{
	SND_CLONE_ASSERT(c != NULL, ("NULL snd_clone"));
	SND_CLONE_ASSERT(tsp != NULL, ("NULL timespec"));

	*tsp = c->tsp;

	return (0);
}