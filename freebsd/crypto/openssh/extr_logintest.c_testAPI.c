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
typedef  int /*<<< orphan*/  username ;
typedef  scalar_t__ time_t ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct passwd {char* pw_name; } ;
struct logininfo {char* progname; char* hostname; int /*<<< orphan*/  line; } ;
struct in_addr {int dummy; } ;
struct hostent {int /*<<< orphan*/ ** h_addr_list; } ;
typedef  int /*<<< orphan*/  stripline ;
typedef  int /*<<< orphan*/  sa_in4 ;
typedef  int /*<<< orphan*/  s_t2 ;
typedef  int /*<<< orphan*/  s_t1 ;
typedef  int /*<<< orphan*/  s_t0 ;
typedef  int /*<<< orphan*/  s_logouttime ;
typedef  int /*<<< orphan*/  s_logintime ;
typedef  int /*<<< orphan*/  cmdstring ;

/* Variables and functions */
 int PAUSE_BEFORE_LOGOUT ; 
 scalar_t__ be_verbose ; 
 char* ctime (scalar_t__*) ; 
 int /*<<< orphan*/  dump_logininfo (struct logininfo*,char*) ; 
 scalar_t__ geteuid () ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ getpid () ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  line_stripname (char*,int /*<<< orphan*/ ,int) ; 
 struct logininfo* login_alloc_entry (int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  login_free_entry (struct logininfo*) ; 
 scalar_t__ login_get_lastlog_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  login_login (struct logininfo*) ; 
 int /*<<< orphan*/  login_logout (struct logininfo*) ; 
 int /*<<< orphan*/  login_set_addr (struct logininfo*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  login_write (struct logininfo*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 scalar_t__ nologtest ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  ttyname (int /*<<< orphan*/ ) ; 

int
testAPI()
{
	struct logininfo *li1;
	struct passwd *pw;
	struct hostent *he;
	struct sockaddr_in sa_in4;
	char cmdstring[256], stripline[8];
	char username[32];
#ifdef HAVE_TIME_H
	time_t t0, t1, t2, logintime, logouttime;
	char s_t0[64],s_t1[64],s_t2[64];
	char s_logintime[64], s_logouttime[64]; /* ctime() strings */
#endif

	printf("**\n** Testing the API...\n**\n");

	pw = getpwuid(getuid());
	strlcpy(username, pw->pw_name, sizeof(username));

	/* gethostname(hostname, sizeof(hostname)); */

	printf("login_alloc_entry test (no host info):\n");

	/* FIXME fake tty more effectively - this could upset some platforms */
	li1 = login_alloc_entry((int)getpid(), username, NULL, ttyname(0));
	strlcpy(li1->progname, "OpenSSH-logintest", sizeof(li1->progname));

	if (be_verbose)
		dump_logininfo(li1, "li1");

	printf("Setting host address info for 'localhost' (may call out):\n");
	if (! (he = gethostbyname("localhost"))) {
		printf("Couldn't set hostname(lookup failed)\n");
	} else {
		/* NOTE: this is messy, but typically a program wouldn't have to set
		 *  any of this, a sockaddr_in* would be already prepared */
		memcpy((void *)&(sa_in4.sin_addr), (void *)&(he->h_addr_list[0][0]),
		       sizeof(struct in_addr));
		login_set_addr(li1, (struct sockaddr *) &sa_in4, sizeof(sa_in4));
		strlcpy(li1->hostname, "localhost", sizeof(li1->hostname));
	}
	if (be_verbose)
		dump_logininfo(li1, "li1");

	if ((int)geteuid() != 0) {
		printf("NOT RUNNING LOGIN TESTS - you are not root!\n");
		return 1;
	}

	if (nologtest)
		return 1;

	line_stripname(stripline, li1->line, sizeof(stripline));

	printf("Performing an invalid login attempt (no type field)\n--\n");
	login_write(li1);
	printf("--\n(Should have written errors to stderr)\n");

#ifdef HAVE_TIME_H
	(void)time(&t0);
	strlcpy(s_t0, ctime(&t0), sizeof(s_t0));
	t1 = login_get_lastlog_time(getuid());
	strlcpy(s_t1, ctime(&t1), sizeof(s_t1));
	printf("Before logging in:\n\tcurrent time is %d - %s\t"
	       "lastlog time is %d - %s\n",
	       (int)t0, s_t0, (int)t1, s_t1);
#endif

	printf("Performing a login on line %s ", stripline);
#ifdef HAVE_TIME_H
	(void)time(&logintime);
	strlcpy(s_logintime, ctime(&logintime), sizeof(s_logintime));
	printf("at %d - %s", (int)logintime, s_logintime);
#endif
	printf("--\n");
	login_login(li1);

	snprintf(cmdstring, sizeof(cmdstring), "who | grep '%s '",
		 stripline);
	system(cmdstring);

	printf("--\nPausing for %d second(s)...\n", PAUSE_BEFORE_LOGOUT);
	sleep(PAUSE_BEFORE_LOGOUT);

	printf("Performing a logout ");
#ifdef HAVE_TIME_H
	(void)time(&logouttime);
	strlcpy(s_logouttime, ctime(&logouttime), sizeof(s_logouttime));
	printf("at %d - %s", (int)logouttime, s_logouttime);
#endif
	printf("\nThe root login shown above should be gone.\n"
	       "If the root login hasn't gone, but another user on the same\n"
	       "pty has, this is OK - we're hacking it here, and there\n"
	       "shouldn't be two users on one pty in reality...\n"
	       "-- ('who' output follows)\n");
	login_logout(li1);

	system(cmdstring);
	printf("-- ('who' output ends)\n");

#ifdef HAVE_TIME_H
	t2 = login_get_lastlog_time(getuid());
	strlcpy(s_t2, ctime(&t2), sizeof(s_t2));
	printf("After logging in, lastlog time is %d - %s\n", (int)t2, s_t2);
	if (t1 == t2)
		printf("The lastlog times before and after logging in are the "
		       "same.\nThis indicates that lastlog is ** NOT WORKING "
		       "CORRECTLY **\n");
	else if (t0 != t2)
		/* We can be off by a second or so, even when recording works fine.
		 * I'm not 100% sure why, but it's true. */
		printf("** The login time and the lastlog time differ.\n"
		       "** This indicates that lastlog is either recording the "
		       "wrong time,\n** or retrieving the wrong entry.\n"
		       "If it's off by less than %d second(s) "
		       "run the test again.\n", PAUSE_BEFORE_LOGOUT);
	else
		printf("lastlog agrees with the login time. This is a good thing.\n");

#endif

	printf("--\nThe output of 'last' shown next should have "
	       "an entry for root \n  on %s for the time shown above:\n--\n",
	       stripline);
	snprintf(cmdstring, sizeof(cmdstring), "last | grep '%s ' | head -3",
		 stripline);
	system(cmdstring);

	printf("--\nEnd of login test.\n");

	login_free_entry(li1);

	return 1;
}