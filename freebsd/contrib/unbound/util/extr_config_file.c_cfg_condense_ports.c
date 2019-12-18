#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct config_file {int* outgoing_avail_ports; } ;

/* Variables and functions */
 int cfg_scan_ports (int*,int) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 scalar_t__ reallocarray (int /*<<< orphan*/ *,size_t,int) ; 

int cfg_condense_ports(struct config_file* cfg, int** avail)
{
	int num = cfg_scan_ports(cfg->outgoing_avail_ports, 65536);
	int i, at = 0;
	*avail = NULL;
	if(num == 0)
		return 0;
	*avail = (int*)reallocarray(NULL, (size_t)num, sizeof(int));
	if(!*avail)
		return 0;
	for(i=0; i<65536; i++) {
		if(cfg->outgoing_avail_ports[i])
			(*avail)[at++] = cfg->outgoing_avail_ports[i];
	}
	log_assert(at == num);
	return num;
}