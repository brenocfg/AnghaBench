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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIOCSHDRCMPLT ; 
 scalar_t__ EAFNOSUPPORT ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 scalar_t__ errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int
pcap_inject_bpf(pcap_t *p, const void *buf, size_t size)
{
	int ret;

	ret = write(p->fd, buf, size);
#ifdef __APPLE__
	if (ret == -1 && errno == EAFNOSUPPORT) {
		/*
		 * In some versions of macOS, there's a bug wherein setting
		 * the BIOCSHDRCMPLT flag causes writes to fail; see, for
		 * example:
		 *
		 *	http://cerberus.sourcefire.com/~jeff/archives/patches/macosx/BIOCSHDRCMPLT-10.3.3.patch
		 *
		 * So, if, on macOS, we get EAFNOSUPPORT from the write, we
		 * assume it's due to that bug, and turn off that flag
		 * and try again.  If we succeed, it either means that
		 * somebody applied the fix from that URL, or other patches
		 * for that bug from
		 *
		 *	http://cerberus.sourcefire.com/~jeff/archives/patches/macosx/
		 *
		 * and are running a Darwin kernel with those fixes, or
		 * that Apple fixed the problem in some macOS release.
		 */
		u_int spoof_eth_src = 0;

		if (ioctl(p->fd, BIOCSHDRCMPLT, &spoof_eth_src) == -1) {
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "send: can't turn off BIOCSHDRCMPLT");
			return (PCAP_ERROR);
		}

		/*
		 * Now try the write again.
		 */
		ret = write(p->fd, buf, size);
	}
#endif /* __APPLE__ */
	if (ret == -1) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "send");
		return (PCAP_ERROR);
	}
	return (ret);
}