#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct port_info {int nqsets; int /*<<< orphan*/  tx_chan; scalar_t__ first_qset; } ;
struct TYPE_6__ {int nports; } ;
struct TYPE_7__ {TYPE_1__ params; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
 struct port_info* adap2pinfo (TYPE_2__*,int) ; 
 int /*<<< orphan*/  send_pktsched_cmd (TYPE_2__*,int,scalar_t__,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bind_qsets(adapter_t *sc)
{
	int i, j;

	for (i = 0; i < (sc)->params.nports; ++i) {
		const struct port_info *pi = adap2pinfo(sc, i);

		for (j = 0; j < pi->nqsets; ++j) {
			send_pktsched_cmd(sc, 1, pi->first_qset + j, -1,
					  -1, pi->tx_chan);

		}
	}
}