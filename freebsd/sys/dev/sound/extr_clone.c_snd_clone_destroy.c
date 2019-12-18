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
struct snd_clone_entry {int /*<<< orphan*/ * devt; int /*<<< orphan*/  head; } ;
struct snd_clone {int /*<<< orphan*/ * devt; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SND_CLONE_ASSERT (int /*<<< orphan*/ ,char*) ; 
 struct snd_clone_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct snd_clone_entry* TAILQ_NEXT (struct snd_clone_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct snd_clone_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

void
snd_clone_destroy(struct snd_clone *c)
{
	struct snd_clone_entry *ce, *tmp;

	SND_CLONE_ASSERT(c != NULL, ("NULL snd_clone"));

	ce = TAILQ_FIRST(&c->head);
	while (ce != NULL) {
		tmp = TAILQ_NEXT(ce, link);
		if (ce->devt != NULL)
			destroy_dev(ce->devt);
		free(ce, M_DEVBUF);
		ce = tmp;
	}

	free(c, M_DEVBUF);
}