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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {char report_ID; int flags; int report_count; int /*<<< orphan*/  pos; scalar_t__ report_size; } ;
struct command {int value; scalar_t__ anyvalue; int debounce; int lastseen; int lastused; TYPE_1__ item; struct command* next; } ;
typedef  int /*<<< orphan*/ * report_desc_t ;
typedef  int /*<<< orphan*/  devnamebuf ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int HIO_VARIABLE ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SIGHUP ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int abs (int) ; 
 int atoi (void*) ; 
 int /*<<< orphan*/  close (int) ; 
 struct command* commands ; 
 scalar_t__ daemon (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  docmd (struct command*,int,char const*,int,char**) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  freecommands (struct command*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ getpid () ; 
 int hid_get_data (char*,TYPE_1__*) ; 
 int /*<<< orphan*/ * hid_get_report_desc (int) ; 
 int /*<<< orphan*/  hid_init (char const*) ; 
 int /*<<< orphan*/  hid_input ; 
 scalar_t__ hid_report_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int isdemon ; 
 scalar_t__ isdigit (char const) ; 
 int open (char const*,int,...) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 void* parse_conf (char const*,int /*<<< orphan*/ *,int,int) ; 
 void* pidfile ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,size_t) ; 
 scalar_t__ reparse ; 
 int /*<<< orphan*/  sighup ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 scalar_t__ write (int,char*,size_t) ; 

int
main(int argc, char **argv)
{
	const char *conf = NULL;
	const char *dev = NULL;
	const char *table = NULL;
	int fd, fp, ch, n, val, i;
	size_t sz, sz1;
	int demon, ignore, dieearly;
	report_desc_t repd;
	char buf[100];
	char devnamebuf[PATH_MAX];
	struct command *cmd;
	int reportid = -1;

	demon = 1;
	ignore = 0;
	dieearly = 0;
	while ((ch = getopt(argc, argv, "c:def:ip:r:t:v")) != -1) {
		switch(ch) {
		case 'c':
			conf = optarg;
			break;
		case 'd':
			demon ^= 1;
			break;
		case 'e':
			dieearly = 1;
			break;
		case 'i':
			ignore++;
			break;
		case 'f':
			dev = optarg;
			break;
		case 'p':
			pidfile = optarg;
			break;
		case 'r':
			reportid = atoi(optarg);
			break;
		case 't':
			table = optarg;
			break;
		case 'v':
			demon = 0;
			verbose++;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (conf == NULL || dev == NULL)
		usage();

	hid_init(table);

	if (dev[0] != '/') {
		snprintf(devnamebuf, sizeof(devnamebuf), "/dev/%s%s",
			 isdigit(dev[0]) ? "uhid" : "", dev);
		dev = devnamebuf;
	}

	fd = open(dev, O_RDWR);
	if (fd < 0)
		err(1, "%s", dev);
	repd = hid_get_report_desc(fd);
	if (repd == NULL)
		err(1, "hid_get_report_desc() failed");

	commands = parse_conf(conf, repd, reportid, ignore);

	sz = (size_t)hid_report_size(repd, hid_input, -1);

	if (verbose)
		printf("report size %zu\n", sz);
	if (sz > sizeof buf)
		errx(1, "report too large");

	(void)signal(SIGHUP, sighup);

	if (demon) {
		fp = open(pidfile, O_WRONLY|O_CREAT, S_IRUSR|S_IRGRP|S_IROTH);
		if (fp < 0)
			err(1, "%s", pidfile);
		if (daemon(0, 0) < 0)
			err(1, "daemon()");
		snprintf(buf, sizeof(buf), "%ld\n", (long)getpid());
		sz1 = strlen(buf);
		if (write(fp, buf, sz1) < 0)
			err(1, "%s", pidfile);
		close(fp);
		isdemon = 1;
	}

	for(;;) {
		n = read(fd, buf, sz);
		if (verbose > 2) {
			printf("read %d bytes:", n);
			for (i = 0; i < n; i++)
				printf(" %02x", buf[i]);
			printf("\n");
		}
		if (n < 0) {
			if (verbose)
				err(1, "read");
			else
				exit(1);
		}
#if 0
		if (n != sz) {
			err(2, "read size");
		}
#endif
		for (cmd = commands; cmd; cmd = cmd->next) {
			if (cmd->item.report_ID != 0 &&
			    buf[0] != cmd->item.report_ID)
				continue;
			if (cmd->item.flags & HIO_VARIABLE)
				val = hid_get_data(buf, &cmd->item);
			else {
				uint32_t pos = cmd->item.pos;
				for (i = 0; i < cmd->item.report_count; i++) {
					val = hid_get_data(buf, &cmd->item);
					if (val == cmd->value)
						break;
					cmd->item.pos += cmd->item.report_size;
				}
				cmd->item.pos = pos;
				val = (i < cmd->item.report_count) ?
				    cmd->value : -1;
			}
			if (cmd->value != val && cmd->anyvalue == 0)
				goto next;
			if ((cmd->debounce == 0) ||
			    ((cmd->debounce == 1) && ((cmd->lastseen == -1) ||
					       (cmd->lastseen != val)))) {
				docmd(cmd, val, dev, argc, argv);
				goto next;
			}
			if ((cmd->debounce > 1) &&
			    ((cmd->lastused == -1) ||
			     (abs(cmd->lastused - val) >= cmd->debounce))) {
				docmd(cmd, val, dev, argc, argv);
				cmd->lastused = val;
				goto next;
			}
next:
			cmd->lastseen = val;
		}

		if (dieearly)
			exit(0);

		if (reparse) {
			struct command *cmds =
			    parse_conf(conf, repd, reportid, ignore);
			if (cmds) {
				freecommands(commands);
				commands = cmds;
			}
			reparse = 0;
		}
	}

	exit(0);
}