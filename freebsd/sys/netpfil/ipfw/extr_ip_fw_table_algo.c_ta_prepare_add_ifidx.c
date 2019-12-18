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
struct tentry_info {scalar_t__ paddr; } ;
struct ta_buf_ifidx {struct ifentry* ife; } ;
struct ip_fw_chain {int dummy; } ;
struct TYPE_6__ {TYPE_2__* iface; struct ifentry* cbdata; int /*<<< orphan*/  cb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct ifentry {TYPE_3__ ic; TYPE_1__ no; } ;
struct TYPE_5__ {int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IF_NAMESIZE ; 
 int /*<<< orphan*/  M_IPFW_TBL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  free (struct ifentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_notifier ; 
 scalar_t__ ipfw_iface_ref (struct ip_fw_chain*,char*,TYPE_3__*) ; 
 struct ifentry* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strnlen (char*,scalar_t__) ; 

__attribute__((used)) static int
ta_prepare_add_ifidx(struct ip_fw_chain *ch, struct tentry_info *tei,
    void *ta_buf)
{
	struct ta_buf_ifidx *tb;
	char *ifname;
	struct ifentry *ife;

	tb = (struct ta_buf_ifidx *)ta_buf;

	/* Check if string is terminated */
	ifname = (char *)tei->paddr;
	if (strnlen(ifname, IF_NAMESIZE) == IF_NAMESIZE)
		return (EINVAL);

	ife = malloc(sizeof(struct ifentry), M_IPFW_TBL, M_WAITOK | M_ZERO);
	ife->ic.cb = if_notifier;
	ife->ic.cbdata = ife;

	if (ipfw_iface_ref(ch, ifname, &ife->ic) != 0) {
		free(ife, M_IPFW_TBL);
		return (EINVAL);
	}

	/* Use ipfw_iface 'ifname' field as stable storage */
	ife->no.name = ife->ic.iface->ifname;

	tb->ife = ife;

	return (0);
}