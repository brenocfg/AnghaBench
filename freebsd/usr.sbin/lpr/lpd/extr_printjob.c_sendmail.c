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
struct stat {int /*<<< orphan*/  st_size; } ;
struct printer {char* printer; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ACCESS 132 
 int /*<<< orphan*/  DORETURN ; 
 int EOF ; 
#define  FATALERR 131 
#define  FILTERERR 130 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_WARNING ; 
#define  NOACCT 129 
#define  OK 128 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 char* _PATH_SENDMAIL ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closeallfds (int) ; 
 int /*<<< orphan*/  closelog () ; 
 int dofork (struct printer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execl (char*,char const*,char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 char* jobname ; 
 char* local_host ; 
 char* origin_host ; 
 int /*<<< orphan*/  pipe (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  tempstderr ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sendmail(struct printer *pp, char *userid, int bombed)
{
	register int i;
	int p[2], s;
	register const char *cp;
	struct stat stb;
	FILE *fp;

	pipe(p);
	if ((s = dofork(pp, DORETURN)) == 0) {		/* child */
		dup2(p[0], STDIN_FILENO);
		closelog();
		closeallfds(3);
		if ((cp = strrchr(_PATH_SENDMAIL, '/')) != NULL)
			cp++;
		else
			cp = _PATH_SENDMAIL;
		execl(_PATH_SENDMAIL, cp, "-t", (char *)0);
		_exit(0);
	} else if (s > 0) {				/* parent */
		dup2(p[1], STDOUT_FILENO);
		printf("To: %s@%s\n", userid, origin_host);
		printf("Subject: %s printer job \"%s\"\n", pp->printer,
			*jobname ? jobname : "<unknown>");
		printf("Reply-To: root@%s\n\n", local_host);
		printf("Your printer job ");
		if (*jobname)
			printf("(%s) ", jobname);

		switch (bombed) {
		case OK:
			cp = "OK";
			printf("\ncompleted successfully\n");
			break;
		default:
		case FATALERR:
			cp = "FATALERR";
			printf("\ncould not be printed\n");
			break;
		case NOACCT:
			cp = "NOACCT";
			printf("\ncould not be printed without an account on %s\n",
			    local_host);
			break;
		case FILTERERR:
			cp = "FILTERERR";
			if (stat(tempstderr, &stb) < 0 || stb.st_size == 0
			    || (fp = fopen(tempstderr, "r")) == NULL) {
				printf("\nhad some errors and may not have printed\n");
				break;
			}
			printf("\nhad the following errors and may not have printed:\n");
			while ((i = getc(fp)) != EOF)
				putchar(i);
			(void) fclose(fp);
			break;
		case ACCESS:
			cp = "ACCESS";
			printf("\nwas not printed because it was not linked to the original file\n");
		}
		fflush(stdout);
		(void) close(STDOUT_FILENO);
	} else {
		syslog(LOG_WARNING, "unable to send mail to %s: %m", userid);
		return;
	}
	(void) close(p[0]);
	(void) close(p[1]);
	wait(NULL);
	syslog(LOG_INFO, "mail sent to user %s about job %s on printer %s (%s)",
	    userid, *jobname ? jobname : "<unknown>", pp->printer, cp);
}