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
typedef  int uint32_t ;
struct tentry_info {int value; int flags; scalar_t__ paddr; } ;
struct table_info {int dummy; } ;
struct ta_buf_ifidx {struct ifentry* ife; } ;
struct ipfw_iface {scalar_t__ resolved; int /*<<< orphan*/  ifindex; } ;
struct iftable_cfg {int /*<<< orphan*/  count; int /*<<< orphan*/  ch; int /*<<< orphan*/  ii; } ;
struct ifidx {int value; } ;
struct TYPE_2__ {struct ipfw_iface* iface; } ;
struct ifentry {int value; TYPE_1__ ic; int /*<<< orphan*/  no; struct iftable_cfg* icfg; } ;

/* Variables and functions */
 int EEXIST ; 
 int EFBIG ; 
 int TEI_FLAGS_DONTADD ; 
 int TEI_FLAGS_UPDATE ; 
 int TEI_FLAGS_UPDATED ; 
 struct ifidx* ifidx_find (struct table_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipfw_iface_add_notify (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ipfw_objhash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ipfw_objhash_lookup_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ta_add_ifidx(void *ta_state, struct table_info *ti, struct tentry_info *tei,
    void *ta_buf, uint32_t *pnum)
{
	struct iftable_cfg *icfg;
	struct ifentry *ife, *tmp;
	struct ta_buf_ifidx *tb;
	struct ipfw_iface *iif;
	struct ifidx *ifi;
	char *ifname;
	uint32_t value;

	tb = (struct ta_buf_ifidx *)ta_buf;
	ifname = (char *)tei->paddr;
	icfg = (struct iftable_cfg *)ta_state;
	ife = tb->ife;

	ife->icfg = icfg;
	ife->value = tei->value;

	tmp = (struct ifentry *)ipfw_objhash_lookup_name(icfg->ii, 0, ifname);

	if (tmp != NULL) {
		if ((tei->flags & TEI_FLAGS_UPDATE) == 0)
			return (EEXIST);

		/* Exchange values in @tmp and @tei */
		value = tmp->value;
		tmp->value = tei->value;
		tei->value = value;

		iif = tmp->ic.iface;
		if (iif->resolved != 0) {
			/* We have to update runtime value, too */
			ifi = ifidx_find(ti, &iif->ifindex);
			ifi->value = ife->value;
		}

		/* Indicate that update has happened instead of addition */
		tei->flags |= TEI_FLAGS_UPDATED;
		*pnum = 0;
		return (0);
	}

	if ((tei->flags & TEI_FLAGS_DONTADD) != 0)
		return (EFBIG);

	/* Link to internal list */
	ipfw_objhash_add(icfg->ii, &ife->no);

	/* Link notifier (possible running its callback) */
	ipfw_iface_add_notify(icfg->ch, &ife->ic);
	icfg->count++;

	tb->ife = NULL;
	*pnum = 1;

	return (0);
}