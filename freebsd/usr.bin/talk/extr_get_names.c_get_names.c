#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  hostname ;
struct TYPE_5__ {void* sa_family; } ;
struct TYPE_4__ {void* sa_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  r_tty; int /*<<< orphan*/  r_name; int /*<<< orphan*/  l_name; int /*<<< orphan*/  id_num; TYPE_2__ ctl_addr; TYPE_1__ addr; int /*<<< orphan*/  vers; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  NAME_SIZE ; 
 int /*<<< orphan*/  TALK_VERSION ; 
 int /*<<< orphan*/  TTY_SIZE ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  get_addrs (char const*,char const*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 char* getlogin () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 TYPE_3__ msg ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

void
get_names(int argc, char *argv[])
{
	char hostname[MAXHOSTNAMELEN];
	char *his_name, *my_name;
	const char *my_machine_name, *his_machine_name;
	const char *his_tty;
	char *cp;

	if (argc < 2 )
		usage();
	if (!isatty(0))
		errx(1, "standard input must be a tty, not a pipe or a file");
	if ((my_name = getlogin()) == NULL) {
		struct passwd *pw;

		if ((pw = getpwuid(getuid())) == NULL)
			errx(1, "you don't exist. Go away");
		my_name = pw->pw_name;
	}
	gethostname(hostname, sizeof (hostname));
	my_machine_name = hostname;
	/* check for, and strip out, the machine name of the target */
	cp = argv[1] + strcspn(argv[1], "@:!");
	if (*cp == '\0') {
		/* this is a local to local talk */
		his_name = argv[1];
		my_machine_name = his_machine_name = "localhost";
	} else {
		if (*cp++ == '@') {
			/* user@host */
			his_name = argv[1];
			his_machine_name = cp;
		} else {
			/* host!user or host:user */
			his_name = cp;
			his_machine_name = argv[1];
		}
		*--cp = '\0';
	}
	if (argc > 2)
		his_tty = argv[2];	/* tty name is arg 2 */
	else
		his_tty = "";
	get_addrs(my_machine_name, his_machine_name);
	/*
	 * Initialize the message template.
	 */
	msg.vers = TALK_VERSION;
	msg.addr.sa_family = htons(AF_INET);
	msg.ctl_addr.sa_family = htons(AF_INET);
	msg.id_num = htonl(0);
	strlcpy(msg.l_name, my_name, NAME_SIZE);
	strlcpy(msg.r_name, his_name, NAME_SIZE);
	strlcpy(msg.r_tty, his_tty, TTY_SIZE);
}