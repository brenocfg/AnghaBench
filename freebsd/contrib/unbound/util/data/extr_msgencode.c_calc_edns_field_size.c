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
typedef  int uint16_t ;
struct edns_option {scalar_t__ opt_len; struct edns_option* next; } ;
struct edns_data {struct edns_option* opt_list; int /*<<< orphan*/  edns_present; } ;

/* Variables and functions */

uint16_t
calc_edns_field_size(struct edns_data* edns)
{
	size_t rdatalen = 0;
	struct edns_option* opt;
	if(!edns || !edns->edns_present) 
		return 0;
	for(opt = edns->opt_list; opt; opt = opt->next) {
		rdatalen += 4 + opt->opt_len;
	}
	/* domain root '.' + type + class + ttl + rdatalen */
	return 1 + 2 + 2 + 4 + 2 + rdatalen;
}