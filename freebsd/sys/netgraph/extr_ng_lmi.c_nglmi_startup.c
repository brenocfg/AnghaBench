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
typedef  TYPE_1__* sc_p ;
struct TYPE_3__ {int local_seq; int /*<<< orphan*/  node; int /*<<< orphan*/  handle; scalar_t__ liv_per_full; scalar_t__ livs; scalar_t__ seq_retries; scalar_t__ remote_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  LMI_ticker ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  ng_callout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nglmi_startup(sc_p sc)
{
	sc->remote_seq = 0;
	sc->local_seq = 1;
	sc->seq_retries = 0;
	sc->livs = sc->liv_per_full - 1;
	/* start off the ticker in 1 sec */
	ng_callout(&sc->handle, sc->node, NULL, hz, LMI_ticker, NULL, 0);
}