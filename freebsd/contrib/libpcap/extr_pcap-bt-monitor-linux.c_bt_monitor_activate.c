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
struct sockaddr_hci {int /*<<< orphan*/  hci_channel; int /*<<< orphan*/  hci_dev; int /*<<< orphan*/  hci_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_5__ {scalar_t__ rfmon; } ;
struct TYPE_6__ {scalar_t__ snapshot; scalar_t__ bufsize; scalar_t__ fd; scalar_t__ selectable_fd; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  buffer; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/ * set_datalink_op; int /*<<< orphan*/  setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  linktype; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  pcap_bluetooth_linux_monitor_header ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BTPROTO_HCI ; 
 scalar_t__ BT_CONTROL_SIZE ; 
 int /*<<< orphan*/  DLT_BLUETOOTH_LINUX_MONITOR ; 
 int /*<<< orphan*/  HCI_CHANNEL_MONITOR ; 
 int /*<<< orphan*/  HCI_DEV_NONE ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_TIMESTAMP ; 
 scalar_t__ bind (scalar_t__,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bt_monitor_inject ; 
 int /*<<< orphan*/  bt_monitor_read ; 
 int /*<<< orphan*/  bt_monitor_setdirection ; 
 int /*<<< orphan*/  bt_monitor_stats ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  install_bpf_program ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_getnonblock_fd ; 
 int /*<<< orphan*/  pcap_setnonblock_fd ; 
 scalar_t__ setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bt_monitor_activate(pcap_t* handle)
{
    struct sockaddr_hci addr;
    int err = PCAP_ERROR;
    int opt;

    if (handle->opt.rfmon) {
        /* monitor mode doesn't apply here */
        return PCAP_ERROR_RFMON_NOTSUP;
    }

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

    handle->bufsize = BT_CONTROL_SIZE + sizeof(pcap_bluetooth_linux_monitor_header) + handle->snapshot;
    handle->linktype = DLT_BLUETOOTH_LINUX_MONITOR;

    handle->read_op = bt_monitor_read;
    handle->inject_op = bt_monitor_inject;
    handle->setfilter_op = install_bpf_program; /* no kernel filtering */
    handle->setdirection_op = bt_monitor_setdirection;
    handle->set_datalink_op = NULL; /* can't change data link type */
    handle->getnonblock_op = pcap_getnonblock_fd;
    handle->setnonblock_op = pcap_setnonblock_fd;
    handle->stats_op = bt_monitor_stats;

    handle->fd = socket(AF_BLUETOOTH, SOCK_RAW, BTPROTO_HCI);
    if (handle->fd < 0) {
        pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
            errno, "Can't create raw socket");
        return PCAP_ERROR;
    }

    handle->buffer = malloc(handle->bufsize);
    if (!handle->buffer) {
        pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
            errno, "Can't allocate dump buffer");
        goto close_fail;
    }

    /* Bind socket to the HCI device */
    addr.hci_family = AF_BLUETOOTH;
    addr.hci_dev = HCI_DEV_NONE;
    addr.hci_channel = HCI_CHANNEL_MONITOR;

    if (bind(handle->fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
            errno, "Can't attach to interface");
        goto close_fail;
    }

    opt = 1;
    if (setsockopt(handle->fd, SOL_SOCKET, SO_TIMESTAMP, &opt, sizeof(opt)) < 0) {
        pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
            errno, "Can't enable time stamp");
        goto close_fail;
    }

    handle->selectable_fd = handle->fd;

    return 0;

close_fail:
    pcap_cleanup_live_common(handle);
    return err;
}