#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_snf {int snf_timeout; int /*<<< orphan*/ * snf_inj; int /*<<< orphan*/  snf_handle; int /*<<< orphan*/  snf_ring; int /*<<< orphan*/  snf_boardnum; } ;
struct TYPE_4__ {char* device; int buffer_size; int timeout; } ;
struct TYPE_5__ {scalar_t__ snapshot; int selectable_fd; int /*<<< orphan*/  cleanup_op; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/  set_datalink_op; int /*<<< orphan*/ * setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  linktype; int /*<<< orphan*/  errbuf; TYPE_1__ opt; struct pcap_snf* priv; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLT_EN10MB ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int SNF_F_PSHARED ; 
 int atoi (char const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snf_getnonblock ; 
 int /*<<< orphan*/  snf_inject ; 
 int snf_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snf_pcap_stats ; 
 int /*<<< orphan*/  snf_platform_cleanup ; 
 int /*<<< orphan*/  snf_read ; 
 int snf_ring_open_id (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snf_set_datalink ; 
 int /*<<< orphan*/  snf_setfilter ; 
 int /*<<< orphan*/  snf_setnonblock ; 
 int snf_start (int /*<<< orphan*/ ) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snf_activate(pcap_t* p)
{
	struct pcap_snf *ps = p->priv;
	char *device = p->opt.device;
	const char *nr = NULL;
	int err;
	int flags = -1, ring_id = -1;

	if (device == NULL) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "device is NULL");
		return -1;
	}

	/* In Libpcap, we set pshared by default if NUM_RINGS is set to > 1.
	 * Since libpcap isn't thread-safe */
	if ((nr = getenv("SNF_FLAGS")) && *nr)
		flags = strtol(nr, NULL, 0);
	else if ((nr = getenv("SNF_NUM_RINGS")) && *nr && atoi(nr) > 1)
		flags = SNF_F_PSHARED;
	else
		nr = NULL;


        /* Allow pcap_set_buffer_size() to set dataring_size.
         * Default is zero which allows setting from env SNF_DATARING_SIZE.
         * pcap_set_buffer_size() is in bytes while snf_open() accepts values
         * between 0 and 1048576 in Megabytes. Values in this range are
         * mapped to 1MB.
         */
	err = snf_open(ps->snf_boardnum,
			0, /* let SNF API parse SNF_NUM_RINGS, if set */
			NULL, /* default RSS, or use SNF_RSS_FLAGS env */
                        (p->opt.buffer_size > 0 && p->opt.buffer_size < 1048576) ? 1048576 : p->opt.buffer_size, /* default to SNF_DATARING_SIZE from env */
			flags, /* may want pshared */
			&ps->snf_handle);
	if (err != 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    err, "snf_open failed");
		return -1;
	}

	if ((nr = getenv("SNF_PCAP_RING_ID")) && *nr) {
		ring_id = (int) strtol(nr, NULL, 0);
	}
	err = snf_ring_open_id(ps->snf_handle, ring_id, &ps->snf_ring);
	if (err != 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    err, "snf_ring_open_id(ring=%d) failed", ring_id);
		return -1;
	}

	/*
	 * Turn a negative snapshot value (invalid), a snapshot value of
	 * 0 (unspecified), or a value bigger than the normal maximum
	 * value, into the maximum allowed value.
	 *
	 * If some application really *needs* a bigger snapshot
	 * length, we should just increase MAXIMUM_SNAPLEN.
	 */
	if (p->snapshot <= 0 || p->snapshot > MAXIMUM_SNAPLEN)
		p->snapshot = MAXIMUM_SNAPLEN;

	if (p->opt.timeout <= 0)
		ps->snf_timeout = -1;
	else
		ps->snf_timeout = p->opt.timeout;

	err = snf_start(ps->snf_handle);
	if (err != 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    err, "snf_start failed");
		return -1;
	}

	/*
	 * "select()" and "poll()" don't work on snf descriptors.
	 */
#ifndef _WIN32
	p->selectable_fd = -1;
#endif /* !_WIN32 */
	p->linktype = DLT_EN10MB;
	p->read_op = snf_read;
	p->inject_op = snf_inject;
	p->setfilter_op = snf_setfilter;
	p->setdirection_op = NULL; /* Not implemented.*/
	p->set_datalink_op = snf_set_datalink;
	p->getnonblock_op = snf_getnonblock;
	p->setnonblock_op = snf_setnonblock;
	p->stats_op = snf_pcap_stats;
	p->cleanup_op = snf_platform_cleanup;
#ifdef SNF_HAVE_INJECT_API
	ps->snf_inj = NULL;
#endif
	return 0;
}