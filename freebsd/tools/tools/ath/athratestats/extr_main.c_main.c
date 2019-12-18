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
typedef  int /*<<< orphan*/  useconds_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ether_addr {int dummy; } ;
struct TYPE_2__ {char* buf; int /*<<< orphan*/  len; } ;
struct ath_ratestats {scalar_t__ s; TYPE_1__ re; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 char* ATH_DEFAULT ; 
 int /*<<< orphan*/  COLOR_BLUE ; 
 int /*<<< orphan*/  COLOR_CYAN ; 
 int /*<<< orphan*/  COLOR_MAGENTA ; 
 int /*<<< orphan*/  COLOR_RED ; 
 int /*<<< orphan*/  COLOR_YELLOW ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  STATS_BUF_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ath_setifname (struct ath_ratestats*,char const*) ; 
 int /*<<< orphan*/  bzero (struct ath_ratestats*,int) ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  clear () ; 
 int do_loop ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 struct ether_addr* ether_aton (char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_and_print_stats (struct ath_ratestats*,struct ether_addr*,int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_pair (int,int /*<<< orphan*/ ,short) ; 
 int /*<<< orphan*/  initscr () ; 
 int /*<<< orphan*/  intrflush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  nonl () ; 
 char* optarg ; 
 int /*<<< orphan*/  pair_content (int /*<<< orphan*/ ,short*,short*) ; 
 int /*<<< orphan*/  refresh () ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char*,char*,float*) ; 
 int /*<<< orphan*/  start_color () ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  use_default_colors () ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	char const *ifname = NULL, *macaddr = NULL;
	int c;
	int do_all = 0;
	struct ether_addr *e;
	struct ath_ratestats r;
	uint8_t *buf;
	useconds_t sleep_period;
	float f;
	short cf, cb;

	ifname = getenv("ATH");
	if (ifname == NULL)
		ifname = ATH_DEFAULT;

	while ((c = getopt(argc, argv, "ahi:m:s:")) != -1) {
		switch (c) {
		case 'a':
			do_all = 1;
			break;
		case 'i':
			ifname = optarg;
			break;
		case 'm':
			macaddr = optarg;
			break;
		case 's':
			sscanf(optarg, "%f", &f);
			do_loop = 1;
			sleep_period = (useconds_t) (f * 1000000.0);
			break;
		default:
			errx(1,
			    "usage: %s [-h] [-i ifname] [-a] [-m macaddr] [-s sleep period]\n",
			    argv[0]);
			/* NOTREACHED */
		}
	}

	if (macaddr == NULL) {
		errx(1, "%s: macaddress wasn't supplied and no -a given\n",
		    argv[0]);
		/* NOTREACHED */
	}
	e = ether_aton(macaddr);
	if (e == NULL)
		err(1, "ether_aton");

	bzero(&r, sizeof(r));

	/*
	 * Persistent buffer for each lookup
	 */
	buf = malloc(STATS_BUF_SIZE);
	if (buf == NULL)
		err(1, "calloc");

	r.re.buf = (char *) buf;
	r.re.len = STATS_BUF_SIZE;

	r.s = socket(AF_INET, SOCK_DGRAM, 0);
	if (r.s < 0) {
		err(1, "socket");
	}

	/* XXX error check */
	ath_setifname(&r, ifname);

	if (do_loop) {
		initscr();
		start_color();
		use_default_colors();
		pair_content(0, &cf, &cb);
		/* Error - medium */
		init_pair(1, COLOR_YELLOW, cb);
		/* Error - high */
		init_pair(2, COLOR_RED, cb);
		/* Sample */
		init_pair(3, COLOR_CYAN, cb);
		/* 250 byte frames */
		init_pair(4, COLOR_BLUE, cb);
		/* 1600 byte frames */
		init_pair(5, COLOR_MAGENTA, cb);
		cbreak();
		noecho();
		nonl();
		nodelay(stdscr, 1);
		intrflush(stdscr, FALSE);
		keypad(stdscr, TRUE);

		while (1) {
			clear();
			move(0, 0);
			fetch_and_print_stats(&r, e, buf);
			refresh();
			usleep(sleep_period);
		}
	} else
		fetch_and_print_stats(&r, e, buf);

	exit(0);
}