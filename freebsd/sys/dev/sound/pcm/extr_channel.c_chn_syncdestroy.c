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
struct pcmchan_syncmember {int id; int /*<<< orphan*/  members; struct pcmchan_syncmember* parent; } ;
struct pcmchan_syncgroup {int id; int /*<<< orphan*/  members; struct pcmchan_syncgroup* parent; } ;
struct pcm_channel {struct pcmchan_syncmember* sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PCM_SG_LOCKASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct pcmchan_syncmember*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pcmchan_syncmember*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  pcmchan_syncgroup ; 
 int /*<<< orphan*/  pcmchan_syncmember ; 
 int /*<<< orphan*/  snd_pcm_syncgroups ; 

int
chn_syncdestroy(struct pcm_channel *c)
{
	struct pcmchan_syncmember *sm;
	struct pcmchan_syncgroup *sg;
	int sg_id;

	sg_id = 0;

	PCM_SG_LOCKASSERT(MA_OWNED);

	if (c->sm != NULL) {
		sm = c->sm;
		sg = sm->parent;
		c->sm = NULL;

		KASSERT(sg != NULL, ("syncmember has null parent"));

		SLIST_REMOVE(&sg->members, sm, pcmchan_syncmember, link);
		free(sm, M_DEVBUF);

		if (SLIST_EMPTY(&sg->members)) {
			SLIST_REMOVE(&snd_pcm_syncgroups, sg, pcmchan_syncgroup, link);
			sg_id = sg->id;
			free(sg, M_DEVBUF);
		}
	}

	return sg_id;
}