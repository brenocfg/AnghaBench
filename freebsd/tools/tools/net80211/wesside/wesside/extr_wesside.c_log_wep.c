#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct pcap_pkthdr {int caplen; int len; struct timeval ts; } ;
struct ieee80211_frame {int caplen; int len; struct timeval ts; } ;
typedef  int /*<<< orphan*/  pkh ;
struct TYPE_2__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  iv; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fsync (int /*<<< orphan*/ ) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (struct pcap_pkthdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  time_print (char*,int,int) ; 
 TYPE_1__ weplog ; 
 int write (int /*<<< orphan*/ ,struct pcap_pkthdr*,int) ; 

void log_wep(struct ieee80211_frame* wh, int len) {
	int rd;
	struct pcap_pkthdr pkh;
	struct timeval tv;
	unsigned char *body = (unsigned char*) (wh+1);

	memset(&pkh, 0, sizeof(pkh));
	pkh.caplen = pkh.len = len;
	if (gettimeofday(&tv, NULL) == -1)
		err(1, "gettimeofday()");
	pkh.ts = tv;
	if (write(weplog.fd, &pkh, sizeof(pkh)) != sizeof(pkh))
		err(1, "write()");

	rd = write(weplog.fd, wh, len);

	if (rd == -1) {
		perror("write()");
		exit(1);
	}
	if (rd != len) {
		time_print("short write %d out of %d\n", rd, len);
		exit(1);
	}

#if 0
	if (fsync(weplog.fd) == -1) {
		perror("fsync()");
		exit(1);
	}
#endif

	memcpy(weplog.iv, body, 3);
	weplog.packets++;
}