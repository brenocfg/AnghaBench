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
struct TYPE_3__ {int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int did_atexit ; 
 int /*<<< orphan*/  pcap_close_all ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
pcap_do_addexit(pcap_t *p)
{
	/*
	 * If we haven't already done so, arrange to have
	 * "pcap_close_all()" called when we exit.
	 */
	if (!did_atexit) {
		if (atexit(pcap_close_all) != 0) {
			/*
			 * "atexit()" failed; let our caller know.
			 */
			strlcpy(p->errbuf, "atexit failed", PCAP_ERRBUF_SIZE);
			return (0);
		}
		did_atexit = 1;
	}
	return (1);
}