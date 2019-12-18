#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netif {TYPE_1__* nif_devdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* Shutdown ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ EFI_SIMPLE_NETWORK ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void
efinet_end(struct netif *nif)
{
	EFI_SIMPLE_NETWORK *net = nif->nif_devdata; 

	if (net == NULL)
		return;

	net->Shutdown(net);
}