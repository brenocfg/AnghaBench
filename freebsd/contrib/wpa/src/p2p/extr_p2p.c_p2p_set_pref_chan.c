#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct p2p_data {TYPE_1__* cfg; } ;
struct p2p_channel {int dummy; } ;
struct TYPE_2__ {unsigned int num_pref_chan; struct p2p_channel* pref_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct p2p_channel*) ; 
 struct p2p_channel* os_memdup (struct p2p_channel const*,unsigned int) ; 

int p2p_set_pref_chan(struct p2p_data *p2p, unsigned int num_pref_chan,
		      const struct p2p_channel *pref_chan)
{
	struct p2p_channel *n;

	if (pref_chan) {
		n = os_memdup(pref_chan,
			      num_pref_chan * sizeof(struct p2p_channel));
		if (n == NULL)
			return -1;
	} else
		n = NULL;

	os_free(p2p->cfg->pref_chan);
	p2p->cfg->pref_chan = n;
	p2p->cfg->num_pref_chan = num_pref_chan;

	return 0;
}