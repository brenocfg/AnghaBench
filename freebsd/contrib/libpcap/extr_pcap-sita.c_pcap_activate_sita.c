#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  device; scalar_t__ rfmon; } ;
struct TYPE_6__ {scalar_t__ snapshot; int fd; scalar_t__ bufsize; scalar_t__ offset; int selectable_fd; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  buffer; int /*<<< orphan*/  linktype; TYPE_1__ opt; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  (* cleanup_op ) (TYPE_2__*) ;int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/ * set_datalink_op; int /*<<< orphan*/  setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int acn_open_live (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  pcap_cleanup_acn (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_getnonblock_fd ; 
 int /*<<< orphan*/  pcap_inject_acn ; 
 int /*<<< orphan*/  pcap_read_acn ; 
 int /*<<< orphan*/  pcap_setdirection_acn ; 
 int /*<<< orphan*/  pcap_setfilter_acn ; 
 int /*<<< orphan*/  pcap_setnonblock_fd ; 
 int /*<<< orphan*/  pcap_stats_acn ; 

__attribute__((used)) static int pcap_activate_sita(pcap_t *handle) {
	int		fd;

	if (handle->opt.rfmon) {
		/*
		 * No monitor mode on SITA devices (they're not Wi-Fi
		 * devices).
		 */
		return PCAP_ERROR_RFMON_NOTSUP;
	}

	/* Initialize some components of the pcap structure. */

	handle->inject_op = pcap_inject_acn;
	handle->setfilter_op = pcap_setfilter_acn;
	handle->setdirection_op = pcap_setdirection_acn;
	handle->set_datalink_op = NULL;	/* can't change data link type */
	handle->getnonblock_op = pcap_getnonblock_fd;
	handle->setnonblock_op = pcap_setnonblock_fd;
	handle->cleanup_op = pcap_cleanup_acn;
	handle->read_op = pcap_read_acn;
	handle->stats_op = pcap_stats_acn;

	fd = acn_open_live(handle->opt.device, handle->errbuf,
	    &handle->linktype);
	if (fd == -1)
		return PCAP_ERROR;

	/*
	 * Turn a negative snapshot value (invalid), a snapshot value of
	 * 0 (unspecified), or a value bigger than the normal maximum
	 * value, into the maximum allowed value.
	 *
	 * If some application really *needs* a bigger snapshot
	 * length, we should just increase MAXIMUM_SNAPLEN.
	 */
	if (handle->snapshot <= 0 || handle->snapshot > MAXIMUM_SNAPLEN)
		handle->snapshot = MAXIMUM_SNAPLEN;

	handle->fd = fd;
	handle->bufsize = handle->snapshot;

	/* Allocate the buffer */

	handle->buffer	 = malloc(handle->bufsize + handle->offset);
	if (!handle->buffer) {
		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		pcap_cleanup_acn(handle);
		return PCAP_ERROR;
	}

	/*
	 * "handle->fd" is a socket, so "select()" and "poll()"
	 * should work on it.
	 */
	handle->selectable_fd = handle->fd;

	return 0;
}