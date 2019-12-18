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
struct socket {TYPE_2__* so_proto; int /*<<< orphan*/  so_vnet; } ;
struct TYPE_4__ {TYPE_1__* pr_usrreqs; } ;
struct TYPE_3__ {int (* pru_connect2 ) (struct socket*,struct socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int stub1 (struct socket*,struct socket*) ; 

int
soconnect2(struct socket *so1, struct socket *so2)
{
	int error;

	CURVNET_SET(so1->so_vnet);
	error = (*so1->so_proto->pr_usrreqs->pru_connect2)(so1, so2);
	CURVNET_RESTORE();
	return (error);
}