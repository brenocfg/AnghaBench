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
 int MAXLINE ; 
 int /*<<< orphan*/  connected ; 
 int creat (char*,int) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getusage (char*) ; 
 char* hostname ; 
 int /*<<< orphan*/  makeargv (char*) ; 
 int margc ; 
 char** margv ; 
 char* mode ; 
 int /*<<< orphan*/  peer ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  recvfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  setpeer0 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 char* tail (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
get(int argc, char *argv[])
{
	int fd;
	int n;
	char *cp;
	char *src;
	char	line[MAXLINE];

	if (argc < 2) {
		strcpy(line, "get ");
		printf("(files) ");
		fgets(&line[strlen(line)], sizeof line - strlen(line), stdin);
		makeargv(line);
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		getusage(argv[0]);
		return;
	}
	if (!connected) {
		for (n = 1; n < argc ; n++)
			if (strrchr(argv[n], ':') == 0) {
				printf("No remote host specified and "
				    "no host given for file '%s'\n", argv[n]);
				getusage(argv[0]);
				return;
			}
	}
	for (n = 1; n < argc ; n++) {
		src = strrchr(argv[n], ':');
		if (src == NULL)
			src = argv[n];
		else {
			char *lcp;

			*src++ = 0;
			lcp = argv[n];
			if (lcp[0] == '[' && lcp[strlen(lcp) - 1] == ']') {
				lcp[strlen(lcp) - 1] = '\0';
				lcp++;
			}
			setpeer0(lcp, NULL);
			if (!connected)
				continue;
		}
		if (argc < 4) {
			cp = argc == 3 ? argv[2] : tail(src);
			fd = creat(cp, 0644);
			if (fd < 0) {
				warn("%s", cp);
				return;
			}
			if (verbose)
				printf("getting from %s:%s to %s [%s]\n",
				    hostname, src, cp, mode);
			recvfile(peer, port, fd, src, mode);
			break;
		}
		cp = tail(src);         /* new .. jdg */
		fd = creat(cp, 0644);
		if (fd < 0) {
			warn("%s", cp);
			continue;
		}
		if (verbose)
			printf("getting from %s:%s to %s [%s]\n",
			    hostname, src, cp, mode);
		recvfile(peer, port, fd, src, mode);
	}
}