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
struct TYPE_4__ {int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 scalar_t__ install_bpf_program (TYPE_1__*,struct bpf_program*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
TcSetFilter(pcap_t *p, struct bpf_program *fp)
{
	if(!fp)
	{
		strncpy(p->errbuf, "setfilter: No filter specified", sizeof(p->errbuf));
		return -1;
	}

	/* Install a user level filter */
	if (install_bpf_program(p, fp) < 0)
	{
		return -1;
	}

	return 0;
}