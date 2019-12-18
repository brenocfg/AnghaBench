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
struct dn_pipe8 {int dummy; } ;
struct dn_flow_set {int dummy; } ;
struct dn_flow_queue8 {int dummy; } ;
struct TYPE_2__ {int schk_count; int fsk_count; int si_count; int queue_count; } ;

/* Variables and functions */
 TYPE_1__ dn_cfg ; 

int
dn_compat_calc_size(void)
{
	int need = 0;
	/* XXX use FreeBSD 8 struct size */
	/* NOTE:
	 * - half scheduler: 		schk_count/2
	 * - all flowset:		fsk_count
	 * - all flowset queues:	queue_count
	 * - all pipe queue:		si_count
	 */
	need += dn_cfg.schk_count * sizeof(struct dn_pipe8) / 2;
	need += dn_cfg.fsk_count * sizeof(struct dn_flow_set);
	need += dn_cfg.si_count * sizeof(struct dn_flow_queue8);
	need += dn_cfg.queue_count * sizeof(struct dn_flow_queue8);

	return need;
}