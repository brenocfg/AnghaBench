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
struct passwd {char* pw_name; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int MAXPATHLEN ; 
 char* _PATH_MAILDIR ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ match (char*,char*) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	FILE *mbox;
	struct passwd *pwd;
	int ch, count, newline;
	const char *file;
	char *sender, *p;
#if MAXPATHLEN > BUFSIZ
	char buf[MAXPATHLEN];
#else
	char buf[BUFSIZ];
#endif

	file = sender = NULL;
	count = -1;
	while ((ch = getopt(argc, argv, "cf:s:")) != -1)
		switch (ch) {
		case 'c':
			count = 0;
			break;
		case 'f':
			file = optarg;
			break;
		case 's':
			sender = optarg;
			for (p = sender; *p; ++p)
				*p = tolower(*p);
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (file == NULL) {
		if (argc) {
			(void)snprintf(buf, sizeof(buf), "%s/%s", _PATH_MAILDIR, *argv);
			file  = buf;
		} else {
			if (!(file = getenv("MAIL"))) {
				if (!(pwd = getpwuid(getuid())))
					errx(1, "no password file entry for you");
				file = pwd->pw_name;
				(void)snprintf(buf, sizeof(buf),
				    "%s/%s", _PATH_MAILDIR, file);
				file = buf;
			}
		}
	}

	/* read from stdin */
	if (strcmp(file, "-") == 0) {
		mbox = stdin;
	} 
	else if ((mbox = fopen(file, "r")) == NULL) {
		errx(1, "can't read %s", file);
	}
	for (newline = 1; fgets(buf, sizeof(buf), mbox);) {
		if (*buf == '\n') {
			newline = 1;
			continue;
		}
		if (newline && !strncmp(buf, "From ", 5) &&
		    (!sender || match(buf + 5, sender))) {
			if (count != -1)
				count++;
			else
				printf("%s", buf);
		}
		newline = 0;
	}
	if (count != -1)
		printf("There %s %d message%s in your incoming mailbox.\n",
		    count == 1 ? "is" : "are", count, count == 1 ? "" : "s"); 
	fclose(mbox);
	exit(0);
}