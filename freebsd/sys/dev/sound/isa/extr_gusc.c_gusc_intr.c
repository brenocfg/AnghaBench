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
typedef  TYPE_3__* sc_p ;
struct TYPE_5__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* intr ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* intr ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ midi_intr; int /*<<< orphan*/ * io; TYPE_1__ pcm_intr; } ;

/* Variables and functions */
 int port_rd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gusc_intr(void *arg)
{
	sc_p scp = (sc_p)arg;
	int did_something;

	do {
		did_something = 0;
		if (scp->pcm_intr.intr != NULL &&
		    (port_rd(scp->io[2], 2) & 1)) {
			(*scp->pcm_intr.intr)(scp->pcm_intr.arg);
			did_something = 1;
		}
		if (scp->midi_intr.intr != NULL &&
		    (port_rd(scp->io[1], 0) & 0x80)) {
			(*scp->midi_intr.intr)(scp->midi_intr.arg);
			did_something = 1;
		}
	} while (did_something != 0);
}