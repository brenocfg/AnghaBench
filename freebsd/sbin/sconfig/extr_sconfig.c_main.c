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

/* Variables and functions */
 int MAXCHAN ; 
 int /*<<< orphan*/  SERIAL_GETVERSIONSTRING ; 
 int adapter_type ; 
 int /*<<< orphan*/  aflag ; 
 scalar_t__ cflag ; 
 int /*<<< orphan*/  clear_stats (int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ eflag ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflag ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_mask () ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ iflag ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char**) ; 
 int* mask ; 
 scalar_t__ mflag ; 
 int open_chan_ctl (int) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_chan (int) ; 
 int /*<<< orphan*/  print_e1_stats (int,int) ; 
 int /*<<< orphan*/  print_e3_stats (int,int) ; 
 int /*<<< orphan*/  print_ifconfig (int) ; 
 int /*<<< orphan*/  print_modems (int,int) ; 
 int /*<<< orphan*/  print_stats (int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setup_chan (int,int,char**) ; 
 scalar_t__ sflag ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int strtol (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tflag ; 
 int /*<<< orphan*/  uflag ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ vflag ; 
 scalar_t__ xflag ; 

int
main (int argc, char **argv)
{
	char *p;
	int fd, need_header, chan_num;

	if (argc > 1 && strcmp(argv[1], "help") == 0)
		usage();

	for (;;) {
		switch (getopt (argc, argv, "mseftucviax")) {
		case -1:
			break;
		case 'a':
			++aflag;
			continue;
		case 'm':
			++mflag;
			continue;
		case 's':
			++sflag;
			continue;
		case 'e':
			++eflag;
			continue;
		case 'f':
			++eflag;
			++fflag;
			continue;
		case 't':
			++tflag;
			continue;
		case 'u':
			++tflag;
			++uflag;
			continue;
		case 'c':
			++cflag;
			continue;
		case 'v':
			++vflag;
			continue;
		case 'i':
			++iflag;
			continue;
		case 'x':
			++xflag;
			continue;
		default:
			usage();
		}
		break;
	}
	argc -= optind;
	argv += optind;

	if (argc <= 0) {
		get_mask ();
		need_header = 1;
		adapter_type = 0;
#ifndef __linux__
		for (; adapter_type < 4; ++adapter_type)
#endif
		{
		for (chan_num=0; chan_num<MAXCHAN; ++chan_num)
			if (mask[adapter_type*16+chan_num/8] & 1 << (chan_num & 7)) {
				fd = open_chan_ctl (chan_num);
				if (vflag) {
#ifdef __linux__
				char buf[256];
				if (ioctl (fd, SERIAL_GETVERSIONSTRING, &buf) >= 0) {
					printf ("Version: %s\n", buf);
					close (fd);
					return (0);
				}
#endif
				}
				if (iflag) {
					print_chan (fd);
					print_ifconfig (fd);
				} else if (sflag||xflag)
					print_stats (fd, need_header);
				else if (mflag)
					print_modems (fd, need_header);
				else if (eflag)
					print_e1_stats (fd, need_header);
				else if (tflag)
					print_e3_stats (fd, need_header);
				else if (cflag)
					clear_stats (fd);
				else
					print_chan (fd);
				close (fd);
				need_header = 0;
			}
		}
		return (0);
	}

	p = argv[0] + strlen (argv[0]);
	while (p > argv[0] && p[-1] >= '0' && p[-1] <= '9')
		--p;
	chan_num = strtol (p, 0, 10);
#ifndef __linux__
	if (strncasecmp ("cx", argv[0], 2)==0)
		adapter_type = 0;
	else if (strncasecmp ("ct", argv[0], 2)==0)
		adapter_type = 1;
	else if (strncasecmp ("cp", argv[0], 2)==0)
		adapter_type = 2;
	else if (strncasecmp ("ce", argv[0], 2)==0)
		adapter_type = 3;
	else {
		fprintf (stderr, "Wrong channel name\n");
		exit (-1);
	}
#endif
	argc--;
	argv++;

	fd = open_chan_ctl (chan_num);
	if (vflag) {
#ifdef __linux__
		char buf[256];
		if (ioctl (fd, SERIAL_GETVERSIONSTRING, &buf) >= 0)
			printf ("Version: %s\n", buf);
#endif
	}
	if (iflag) {
		print_chan (fd);
		print_ifconfig (fd);
		close (fd);
		return (0);
	}
	if (sflag||xflag) {
		print_stats (fd, 1);
		close (fd);
		return (0);
	}
	if (mflag) {
		print_modems (fd, 1);
		close (fd);
		return (0);
	}
	if (eflag) {
		print_e1_stats (fd, 1);
		close (fd);
		return (0);
	}
	if (tflag) {
		print_e3_stats (fd, 1);
		close (fd);
		return (0);
	}
	if (cflag) {
		clear_stats (fd);
		close (fd);
		return (0);
	}
	if (argc > 0)
		setup_chan (fd, argc, argv);
	else
		print_chan (fd);
	close (fd);
	return (0);
}