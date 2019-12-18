#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; } ;
struct TYPE_5__ {int link_nr; int delay; scalar_t__ bandwidth; int burst; TYPE_1__ oid; } ;
struct dn_schk {TYPE_2__ link; int /*<<< orphan*/ * profile; } ;
struct dn_link {int link_nr; int delay; int burst; scalar_t__ bandwidth; TYPE_1__ oid; } ;
struct dn_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int) ; 
 int /*<<< orphan*/  DN_BH_WLOCK () ; 
 int /*<<< orphan*/  DN_BH_WUNLOCK () ; 
 int DN_MAX_ID ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 TYPE_3__ dn_cfg ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hz ; 
 struct dn_schk* locate_scheduler (int) ; 
 int /*<<< orphan*/  schk_reset_credit (struct dn_schk*) ; 
 int /*<<< orphan*/  update_red (struct dn_schk*) ; 

__attribute__((used)) static int
config_link(struct dn_link *p, struct dn_id *arg)
{
	int i;

	if (p->oid.len != sizeof(*p)) {
		D("invalid pipe len %d", p->oid.len);
		return EINVAL;
	}
	i = p->link_nr;
	if (i <= 0 || i >= DN_MAX_ID)
		return EINVAL;
	/*
	 * The config program passes parameters as follows:
	 * bw = bits/second (0 means no limits),
	 * delay = ms, must be translated into ticks.
	 * qsize = slots/bytes
	 * burst ???
	 */
	p->delay = (p->delay * hz) / 1000;
	/* Scale burst size: bytes -> bits * hz */
	p->burst *= 8 * hz;

	DN_BH_WLOCK();
	/* do it twice, base link and FIFO link */
	for (; i < 2*DN_MAX_ID; i += DN_MAX_ID) {
	    struct dn_schk *s = locate_scheduler(i);
	    if (s == NULL) {
		DN_BH_WUNLOCK();
		D("sched %d not found", i);
		return EINVAL;
	    }
	    /* remove profile if exists */
	    if (s->profile) {
		free(s->profile, M_DUMMYNET);
		s->profile = NULL;
	    }
	    /* copy all parameters */
	    s->link.oid = p->oid;
	    s->link.link_nr = i;
	    s->link.delay = p->delay;
	    if (s->link.bandwidth != p->bandwidth) {
		/* XXX bandwidth changes, need to update red params */
	    s->link.bandwidth = p->bandwidth;
		update_red(s);
	    }
	    s->link.burst = p->burst;
	    schk_reset_credit(s);
	}
	dn_cfg.id++;
	DN_BH_WUNLOCK();
	return 0;
}