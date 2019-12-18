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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * chan_send_cnt; int /*<<< orphan*/  data_sg_cnt; int /*<<< orphan*/  data_vaddr_cnt; int /*<<< orphan*/  data_bio_cnt; } ;
struct storvsc_softc {int hs_nchan; TYPE_1__ sysctl_data; int /*<<< orphan*/ * hs_sel_chan; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int /*<<< orphan*/  OID_AUTO ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_ULONG (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 struct storvsc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int vmbus_chan_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
storvsc_sysctl(device_t dev)
{
	struct sysctl_oid_list *child;
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid *ch_tree, *chid_tree;
	struct storvsc_softc *sc;
	char name[16];
	int i;

	sc = device_get_softc(dev);
	ctx = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));

	SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "data_bio_cnt", CTLFLAG_RW,
		&sc->sysctl_data.data_bio_cnt, "# of bio data block");
	SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "data_vaddr_cnt", CTLFLAG_RW,
		&sc->sysctl_data.data_vaddr_cnt, "# of vaddr data block");
	SYSCTL_ADD_ULONG(ctx, child, OID_AUTO, "data_sg_cnt", CTLFLAG_RW,
		&sc->sysctl_data.data_sg_cnt, "# of sg data block");

	/* dev.storvsc.UNIT.channel */
	ch_tree = SYSCTL_ADD_NODE(ctx, child, OID_AUTO, "channel",
		CTLFLAG_RD | CTLFLAG_MPSAFE, 0, "");
	if (ch_tree == NULL)
		return;

	for (i = 0; i < sc->hs_nchan; i++) {
		uint32_t ch_id;

		ch_id = vmbus_chan_id(sc->hs_sel_chan[i]);
		snprintf(name, sizeof(name), "%d", ch_id);
		/* dev.storvsc.UNIT.channel.CHID */
		chid_tree = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(ch_tree),
			OID_AUTO, name, CTLFLAG_RD | CTLFLAG_MPSAFE, 0, "");
		if (chid_tree == NULL)
			return;
		/* dev.storvsc.UNIT.channel.CHID.send_req */
		SYSCTL_ADD_ULONG(ctx, SYSCTL_CHILDREN(chid_tree), OID_AUTO,
			"send_req", CTLFLAG_RD, &sc->sysctl_data.chan_send_cnt[i],
			"# of request sending from this channel");
	}
}