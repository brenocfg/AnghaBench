#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct proto_md {int /*<<< orphan*/  bd_map; int /*<<< orphan*/  bd_tag; int /*<<< orphan*/  physaddr; } ;
struct TYPE_3__ {int op; } ;
struct TYPE_4__ {TYPE_1__ sync; } ;
struct proto_ioc_busdma {TYPE_2__ u; } ;
struct proto_busdma {int dummy; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
proto_busdma_sync(struct proto_busdma *busdma, struct proto_md *md,
    struct proto_ioc_busdma *ioc)
{
	u_int ops;

	ops = BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE |
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE;
	if (ioc->u.sync.op & ~ops)
		return (EINVAL);
	if (!md->physaddr)
		return (ENXIO);
	bus_dmamap_sync(md->bd_tag, md->bd_map, ioc->u.sync.op);
	return (0);
}