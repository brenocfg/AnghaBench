#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cfg {int /*<<< orphan*/  fd; int /*<<< orphan*/  unit; } ;
typedef  int /*<<< orphan*/  p ;
struct TYPE_7__ {int* ifm_ulist; int ifm_count; int ifm_current; } ;
struct TYPE_6__ {int ifr_media; } ;
struct TYPE_8__ {TYPE_2__ es_ifmr; TYPE_1__ es_ifr; int /*<<< orphan*/  es_port; } ;
typedef  TYPE_3__ etherswitch_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int IFMEDIAREQ_NULISTENTRIES ; 
 int IFM_IMASK ; 
 int IFM_TYPE (int) ; 
 int /*<<< orphan*/  IOETHERSWITCHGETPORT ; 
 int /*<<< orphan*/  IOETHERSWITCHSETPORT ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int get_media_subtype (int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int
set_port_media(struct cfg *cfg, int argc, char *argv[])
{
	etherswitch_port_t p;
	int ifm_ulist[IFMEDIAREQ_NULISTENTRIES];
	int subtype;

	if (argc < 2)
		return (-1);

	bzero(&p, sizeof(p));
	p.es_port = cfg->unit;
	p.es_ifmr.ifm_ulist = ifm_ulist;
	p.es_ifmr.ifm_count = IFMEDIAREQ_NULISTENTRIES;
	if (ioctl(cfg->fd, IOETHERSWITCHGETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHGETPORT)");
	if (p.es_ifmr.ifm_count == 0)
		return (0);
	subtype = get_media_subtype(IFM_TYPE(ifm_ulist[0]), argv[1]);
	p.es_ifr.ifr_media = (p.es_ifmr.ifm_current & IFM_IMASK) |
	        IFM_TYPE(ifm_ulist[0]) | subtype;
	if (ioctl(cfg->fd, IOETHERSWITCHSETPORT, &p) != 0)
		err(EX_OSERR, "ioctl(IOETHERSWITCHSETPORT)");
	return (0);
}