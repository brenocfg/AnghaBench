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
struct params {char* fname; int mtu; int rx; int tx; int tap; int prga_len; void* state; int /*<<< orphan*/  mac; int /*<<< orphan*/  ap; int /*<<< orphan*/  seq; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 void* S_START ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_more_prga (struct params*) ; 
 int /*<<< orphan*/  get_prga (struct params*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  load_prga (struct params*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct params*,int /*<<< orphan*/ ,int) ; 
 int open_rx (char*) ; 
 int open_tap (char*) ; 
 int open_tx (char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  printf (char*) ; 
 int set_iface_mac (char*,int /*<<< orphan*/ ) ; 
 int str2mac (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  transmit (struct params*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	struct params p;
	char *iface = "wlan0";
	char *tap = "tap0";
	int ch;

	memset(&p, 0, sizeof(p));
	p.fname = "prga.log";
	memcpy(p.mac, "\x00\x00\xde\xfa\xce\x0d", 6);
	p.state = S_START;
	p.mtu = 1500;
	p.seq = getpid();

	while ((ch = getopt(argc, argv, "hb:t:")) != -1) {
		switch (ch) {
		case 'b':
			if (str2mac(p.ap, optarg) == -1) {
				printf("Can't parse BSSID\n");
				exit(1);
			}
			break;

		case 't':
			tap = optarg;
			break;

		case 'h':
		default:
			usage(argv[0]);
			break;
		}
	}

	/* init */
	if ((p.rx = open_rx(iface)) == -1)
		err(1, "open_rx()");
	if ((p.tx = open_tx(iface)) == -1)
		err(1, "open_tx()");

	if ((p.tap = open_tap(tap)) == -1)
		err(1, "open_tap()");
	if (set_iface_mac(tap, p.mac) == -1)
		err(1, "set_iface_mac()");

	printf("Obtaining PRGA\n");
	/* make sure we got some prga */
	load_prga(&p);

	while (p.prga_len == 0)
		get_prga(&p);

	/* lets grab some more */
	while (p.prga_len < p.mtu)
		get_more_prga(&p);

	/* transmit */
	p.state = S_START;
	while (1)
		transmit(&p);

	exit(0);
}