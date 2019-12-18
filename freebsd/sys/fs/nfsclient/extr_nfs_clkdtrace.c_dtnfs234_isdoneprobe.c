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
typedef  scalar_t__ dtrace_id_t ;
struct TYPE_2__ {scalar_t__ nr_v4_id_done; scalar_t__ nr_v3_id_done; scalar_t__ nr_v2_id_done; } ;

/* Variables and functions */
 int NFSV41_NPROCS ; 
 TYPE_1__* dtnfsclient_rpcs ; 

__attribute__((used)) static int
dtnfs234_isdoneprobe(dtrace_id_t id)
{
	int i;

	for (i = 0; i < NFSV41_NPROCS + 1; i++) {
		if (dtnfsclient_rpcs[i].nr_v4_id_done == id ||
		    dtnfsclient_rpcs[i].nr_v3_id_done == id ||
		    dtnfsclient_rpcs[i].nr_v2_id_done == id)
			return (1);
	}
	return (0);
}