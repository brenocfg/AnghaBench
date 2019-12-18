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
struct TYPE_6__ {int tstamp_type; scalar_t__ nocapture_local; scalar_t__ protocol; int /*<<< orphan*/  tstamp_precision; scalar_t__ immediate; scalar_t__ rfmon; scalar_t__ promisc; scalar_t__ buffer_size; scalar_t__ timeout; } ;
struct TYPE_7__ {scalar_t__ bpf_codegen_flags; TYPE_1__ opt; scalar_t__ snapshot; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  can_set_rfmon_op; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_TSTAMP_PRECISION_MICRO ; 
 int /*<<< orphan*/  initialize_ops (TYPE_2__*) ; 
 TYPE_2__* pcap_alloc_pcap_t (char*,size_t) ; 
 int /*<<< orphan*/  pcap_cant_set_rfmon ; 
 int /*<<< orphan*/  pcap_setnonblock_unactivated ; 

pcap_t *
pcap_create_common(char *ebuf, size_t size)
{
	pcap_t *p;

	p = pcap_alloc_pcap_t(ebuf, size);
	if (p == NULL)
		return (NULL);

	/*
	 * Default to "can't set rfmon mode"; if it's supported by
	 * a platform, the create routine that called us can set
	 * the op to its routine to check whether a particular
	 * device supports it.
	 */
	p->can_set_rfmon_op = pcap_cant_set_rfmon;

	/*
	 * If pcap_setnonblock() is called on a not-yet-activated
	 * pcap_t, default to setting a flag and turning
	 * on non-blocking mode when activated.
	 */
	p->setnonblock_op = pcap_setnonblock_unactivated;

	initialize_ops(p);

	/* put in some defaults*/
	p->snapshot = 0;		/* max packet size unspecified */
	p->opt.timeout = 0;		/* no timeout specified */
	p->opt.buffer_size = 0;		/* use the platform's default */
	p->opt.promisc = 0;
	p->opt.rfmon = 0;
	p->opt.immediate = 0;
	p->opt.tstamp_type = -1;	/* default to not setting time stamp type */
	p->opt.tstamp_precision = PCAP_TSTAMP_PRECISION_MICRO;
	/*
	 * Platform-dependent options.
	 */
#ifdef __linux__
	p->opt.protocol = 0;
#endif
#ifdef _WIN32
	p->opt.nocapture_local = 0;
#endif

	/*
	 * Start out with no BPF code generation flags set.
	 */
	p->bpf_codegen_flags = 0;

	return (p);
}