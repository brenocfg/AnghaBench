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
struct pcap_win {int nonblock; int /*<<< orphan*/  adapter; } ;
struct TYPE_4__ {int timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  errbuf; TYPE_1__ opt; struct pcap_win* priv; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PacketSetReadTimeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pcap_win32_err_to_str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcap_setnonblock_npf(pcap_t *p, int nonblock)
{
	struct pcap_win *pw = p->priv;
	int newtimeout;
	char win_errbuf[PCAP_ERRBUF_SIZE+1];

	if (nonblock) {
		/*
		 * Set the packet buffer timeout to -1 for non-blocking
		 * mode.
		 */
		newtimeout = -1;
	} else {
		/*
		 * Restore the timeout set when the device was opened.
		 * (Note that this may be -1, in which case we're not
		 * really leaving non-blocking mode.  However, although
		 * the timeout argument to pcap_set_timeout() and
		 * pcap_open_live() is an int, you're not supposed to
		 * supply a negative value, so that "shouldn't happen".)
		 */
		newtimeout = p->opt.timeout;
	}
	if (!PacketSetReadTimeout(pw->adapter, newtimeout)) {
		pcap_win32_err_to_str(GetLastError(), win_errbuf);
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "PacketSetReadTimeout: %s", win_errbuf);
		return (-1);
	}
	pw->nonblock = (newtimeout == -1);
	return (0);
}