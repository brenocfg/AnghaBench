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
struct thread {struct seltd* td_sel; } ;
struct seltd {TYPE_1__* st_free2; TYPE_2__* st_free1; } ;
struct TYPE_4__ {void* sf_cookie; struct seltd* sf_td; } ;
struct TYPE_3__ {void* sf_cookie; struct seltd* sf_td; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  selfd_zone ; 
 void* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
selfdalloc(struct thread *td, void *cookie)
{
	struct seltd *stp;

	stp = td->td_sel;
	if (stp->st_free1 == NULL)
		stp->st_free1 = uma_zalloc(selfd_zone, M_WAITOK|M_ZERO);
	stp->st_free1->sf_td = stp;
	stp->st_free1->sf_cookie = cookie;
	if (stp->st_free2 == NULL)
		stp->st_free2 = uma_zalloc(selfd_zone, M_WAITOK|M_ZERO);
	stp->st_free2->sf_td = stp;
	stp->st_free2->sf_cookie = cookie;
}