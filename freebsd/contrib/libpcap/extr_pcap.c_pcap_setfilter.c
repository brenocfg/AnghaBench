#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bpf_program {int dummy; } ;
struct TYPE_4__ {int (* setfilter_op ) (TYPE_1__*,struct bpf_program*) ;} ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int stub1 (TYPE_1__*,struct bpf_program*) ; 

int
pcap_setfilter(pcap_t *p, struct bpf_program *fp)
{
	return (p->setfilter_op(p, fp));
}