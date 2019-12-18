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
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 TYPE_1__* NA (struct ifnet*) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 

void *
nm_os_send_up(struct ifnet *ifp, struct mbuf *m, struct mbuf *prev)
{
	NA(ifp)->if_input(ifp, m);
	return NULL;
}