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
struct stat {int /*<<< orphan*/  st_size; } ;
struct TYPE_2__ {int /*<<< orphan*/  o_request; } ;

/* Variables and functions */
 int MAXLINE ; 
 size_t OPT_TSIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  connected ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 char* hostname ; 
 int /*<<< orphan*/  makeargv (char*) ; 
 int margc ; 
 char** margv ; 
 char* mode ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* options ; 
 int /*<<< orphan*/  peer ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putusage (char*) ; 
 int /*<<< orphan*/  setpeer0 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 char* tail (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  xmitfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 

__attribute__((used)) static void
put(int argc, char *argv[])
{
	int	fd;
	int	n;
	char	*cp, *targ;
	char	line[MAXLINE];
	struct stat sb;

	if (argc < 2) {
		strcpy(line, "send ");
		printf("(file) ");
		fgets(&line[strlen(line)], sizeof line - strlen(line), stdin);
		makeargv(line);
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		putusage(argv[0]);
		return;
	}
	targ = argv[argc - 1];
	if (strrchr(argv[argc - 1], ':')) {
		char *lcp;

		for (n = 1; n < argc - 1; n++)
			if (strchr(argv[n], ':')) {
				putusage(argv[0]);
				return;
			}
		lcp = argv[argc - 1];
		targ = strrchr(lcp, ':');
		*targ++ = 0;
		if (lcp[0] == '[' && lcp[strlen(lcp) - 1] == ']') {
			lcp[strlen(lcp) - 1] = '\0';
			lcp++;
		}
		setpeer0(lcp, NULL);
	}
	if (!connected) {
		printf("No target machine specified.\n");
		return;
	}
	if (argc < 4) {
		cp = argc == 2 ? tail(targ) : argv[1];
		fd = open(cp, O_RDONLY);
		if (fd < 0) {
			warn("%s", cp);
			return;
		}

		if (fstat(fd, &sb) < 0) {
			warn("%s", cp);
			close(fd);
			return;
		}
		asprintf(&options[OPT_TSIZE].o_request, "%ju", sb.st_size);

		if (verbose)
			printf("putting %s to %s:%s [%s]\n",
			    cp, hostname, targ, mode);
		xmitfile(peer, port, fd, targ, mode);
		close(fd);
		return;
	}
				/* this assumes the target is a directory */
				/* on a remote unix system.  hmmmm.  */
	cp = strchr(targ, '\0');
	*cp++ = '/';
	for (n = 1; n < argc - 1; n++) {
		strcpy(cp, tail(argv[n]));
		fd = open(argv[n], O_RDONLY);
		if (fd < 0) {
			warn("%s", argv[n]);
			continue;
		}

		if (fstat(fd, &sb) < 0) {
			warn("%s", argv[n]);
			continue;
		}
		asprintf(&options[OPT_TSIZE].o_request, "%ju", sb.st_size);

		if (verbose)
			printf("putting %s to %s:%s [%s]\n",
			    argv[n], hostname, targ, mode);
		xmitfile(peer, port, fd, targ, mode);
	}
}