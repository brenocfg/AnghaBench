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
struct daemon {int /*<<< orphan*/  rand; TYPE_1__* cfg; } ;
struct TYPE_2__ {int* outgoing_avail_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_exit (char*) ; 
 int ub_random_max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int daemon_get_shufport(struct daemon* daemon, int* shufport)
{
	int i, n, k, temp;
	int avail = 0;
	for(i=0; i<65536; i++) {
		if(daemon->cfg->outgoing_avail_ports[i]) {
			shufport[avail++] = daemon->cfg->
				outgoing_avail_ports[i];
		}
	}
	if(avail == 0)
		fatal_exit("no ports are permitted for UDP, add "
			"with outgoing-port-permit");
        /* Knuth shuffle */
	n = avail;
	while(--n > 0) {
		k = ub_random_max(daemon->rand, n+1); /* 0<= k<= n */
		temp = shufport[k];
		shufport[k] = shufport[n];
		shufport[n] = temp;
	}
	return avail;
}