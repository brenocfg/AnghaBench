#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct params {int bint; int chan; int tx; int rx; int tap; int /*<<< orphan*/  mac; int /*<<< orphan*/  wep_len; int /*<<< orphan*/  wep_key; int /*<<< orphan*/ * ssid; int /*<<< orphan*/  blast; int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_event (struct params*) ; 
 int open_rx (char*) ; 
 int open_tap (char*) ; 
 int open_tx (char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  printf (char*) ; 
 int set_iface_mac (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str2mac (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  str2wep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	char *iface = "wlan0";
	char *tap = "tap0";
	struct params p;
	int ch;

	/* default params */
	memset(&p, 0, sizeof(p));
	memcpy(p.mac, "\x00\x00\xde\xfa\xce\x0d", 6);
	strcpy(p.ssid, "sorbo");
	p.bint = 500*1000;
	p.seq = getpid();
	if (gettimeofday(&p.blast, NULL) == -1)
		err(1, "gettimeofday()");
	p.chan = 3;

	while ((ch = getopt(argc, argv, "hi:s:m:w:c:t:")) != -1) {
		switch (ch) {
		case 'i':
			iface = optarg;
			break;
		case 't':
			tap = optarg;
			break;

		case 'c':
			p.chan = atoi(optarg);
			break;

		case 's':
			strncpy(p.ssid, optarg, sizeof(p.ssid)-1);
			p.ssid[sizeof(p.ssid)-1] = 0; 
			break;

		case 'm':
			str2mac(p.mac, optarg);
			break;

		case 'w':
			if (str2wep(p.wep_key, &p.wep_len, optarg)) {
				printf("Error parsing WEP key\n");
				exit(1);
			}
			break;

		case 'h':
		default:
			usage(argv[0]);
			break;
		}
	}

	/* init */
	if ((p.tx = open_tx(iface)) == -1)
		err(1, "open_tx()");
	if ((p.rx = open_rx(iface)) == -1)
		err(1, "open_rx()");

	if ((p.tap = open_tap(tap)) == -1)
		err(1, "open_tap()");
	if (set_iface_mac(tap, p.mac) == -1)
		err(1, "set_iface_mac()");

	while (1) {
		next_event(&p);
	}

	exit(0);
}