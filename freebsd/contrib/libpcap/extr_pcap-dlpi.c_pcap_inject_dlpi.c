#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_dlpi {scalar_t__ send_fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; struct pcap_dlpi* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int dlrawdatareq (scalar_t__,void const*,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int
pcap_inject_dlpi(pcap_t *p, const void *buf, size_t size)
{
#ifdef DL_HP_RAWDLS
	struct pcap_dlpi *pd = p->priv;
#endif
	int ret;

#if defined(DLIOCRAW)
	ret = write(p->fd, buf, size);
	if (ret == -1) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "send");
		return (-1);
	}
#elif defined(DL_HP_RAWDLS)
	if (pd->send_fd < 0) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "send: Output FD couldn't be opened");
		return (-1);
	}
	ret = dlrawdatareq(pd->send_fd, buf, size);
	if (ret == -1) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "send");
		return (-1);
	}
	/*
	 * putmsg() returns either 0 or -1; it doesn't indicate how
	 * many bytes were written (presumably they were all written
	 * or none of them were written).  OpenBSD's pcap_inject()
	 * returns the number of bytes written, so, for API compatibility,
	 * we return the number of bytes we were told to write.
	 */
	ret = size;
#else /* no raw mode */
	/*
	 * XXX - this is a pain, because you might have to extract
	 * the address from the packet and use it in a DL_UNITDATA_REQ
	 * request.  That would be dependent on the link-layer type.
	 *
	 * I also don't know what SAP you'd have to bind the descriptor
	 * to, or whether you'd need separate "receive" and "send" FDs,
	 * nor do I know whether you'd need different bindings for
	 * D/I/X Ethernet and 802.3, or for {FDDI,Token Ring} plus
	 * 802.2 and {FDDI,Token Ring} plus 802.2 plus SNAP.
	 *
	 * So, for now, we just return a "you can't send" indication,
	 * and leave it up to somebody with a DLPI-based system lacking
	 * both DLIOCRAW and DL_HP_RAWDLS to supply code to implement
	 * packet transmission on that system.  If they do, they should
	 * send it to us - but should not send us code that assumes
	 * Ethernet; if the code doesn't work on non-Ethernet interfaces,
	 * it should check "p->linktype" and reject the send request if
	 * it's anything other than DLT_EN10MB.
	 */
	strlcpy(p->errbuf, "send: Not supported on this version of this OS",
	    PCAP_ERRBUF_SIZE);
	ret = -1;
#endif /* raw mode */
	return (ret);
}