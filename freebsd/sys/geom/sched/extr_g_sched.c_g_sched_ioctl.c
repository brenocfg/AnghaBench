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
typedef  int /*<<< orphan*/  u_long ;
struct thread {int dummy; } ;
struct g_provider {TYPE_1__* geom; } ;
struct g_geom {int (* ioctl ) (TYPE_2__*,int /*<<< orphan*/ ,void*,int,struct thread*) ;} ;
struct g_consumer {TYPE_2__* provider; } ;
struct TYPE_4__ {struct g_geom* geom; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int ENOIOCTL ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,void*,int,struct thread*) ; 

__attribute__((used)) static int
g_sched_ioctl(struct g_provider *pp, u_long cmd, void *data, int fflag,
    struct thread *td)
{
	struct g_consumer *cp;
	struct g_geom *gp;

	cp = LIST_FIRST(&pp->geom->consumer);
	if (cp == NULL)
		return (ENOIOCTL);
	gp = cp->provider->geom;
	if (gp->ioctl == NULL)
		return (ENOIOCTL);
	return (gp->ioctl(cp->provider, cmd, data, fflag, td));
}