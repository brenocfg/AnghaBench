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
typedef  int u_long ;
struct thread {int dummy; } ;
struct proto_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  busdma; int /*<<< orphan*/  res; } ;
struct proto_res {TYPE_1__ r_d; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_size; } ;
struct proto_ioc_region {int /*<<< orphan*/  address; int /*<<< orphan*/  size; } ;
struct proto_ioc_busdma {int dummy; } ;
struct cdev {struct proto_res* si_drv2; struct proto_softc* si_drv1; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOIOCTL ; 
#define  PROTO_IOC_BUSDMA 129 
#define  PROTO_IOC_REGION 128 
 int /*<<< orphan*/  PROTO_RES_BUSDMA ; 
 int /*<<< orphan*/  PROTO_RES_PCICFG ; 
 int proto_busdma_ioctl (struct proto_softc*,int /*<<< orphan*/ ,struct proto_ioc_busdma*,struct thread*) ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
proto_ioctl(struct cdev *cdev, u_long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	struct proto_ioc_region *region;
	struct proto_ioc_busdma *busdma;
	struct proto_res *r;
	struct proto_softc *sc;
	int error;

	sc = cdev->si_drv1;
	r = cdev->si_drv2;

	error = 0;
	switch (cmd) {
	case PROTO_IOC_REGION:
		if (r->r_type == PROTO_RES_BUSDMA) {
			error = EINVAL;
			break;
		}
		region = (struct proto_ioc_region *)data;
		region->size = r->r_size;
		if (r->r_type == PROTO_RES_PCICFG)
			region->address = 0;
		else
			region->address = rman_get_start(r->r_d.res);
		break;
	case PROTO_IOC_BUSDMA:
		if (r->r_type != PROTO_RES_BUSDMA) {
			error = EINVAL;
			break;
		}
		busdma = (struct proto_ioc_busdma *)data;
		error = proto_busdma_ioctl(sc, r->r_d.busdma, busdma, td);
		break;
	default:
		error = ENOIOCTL;
		break;
	}
	return (error);
}