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
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ EAFNOSUPPORT ; 
 int /*<<< orphan*/  EPROTONOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int LINE_LENGTH ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errc (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ isblank (char) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  process_cmd (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_file (char*,int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strchr (char*,char) ; 

int
main(int argc, char **argv)
{
	char	 line[LINE_LENGTH];
	char	*p;
	int	 i, s, s6;

	s = -1;
	s6 = -1;
#ifdef INET
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == -1 && errno != EAFNOSUPPORT)
		err(1, "can't open IPv4 socket");
#endif
#ifdef INET6
	s6 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
	if (s6 == -1 && errno != EAFNOSUPPORT)
		err(1, "can't open IPv6 socket");
#endif
	if (s == -1 && s6 == -1)
		errc(1, EPROTONOSUPPORT, "can't open socket");

	if (argc < 2) {
		if (isatty(STDIN_FILENO)) {
			printf("multicast membership test program; "
			    "enter ? for list of commands\n");
		}
		do {
			if (fgets(line, sizeof(line), stdin) != NULL) {
				if (line[0] != 'f')
					process_cmd(line, s, s6, stdin);
				else {
					/* Get the filename */
					for (i = 1; isblank(line[i]); i++);
					if ((p = (char*)strchr(line, '\n'))
					    != NULL)
						*p = '\0';
					process_file(&line[i], s, s6);
				}
			}
		} while (!feof(stdin));
	} else {
		for (i = 1; i < argc; i++) {
			process_file(argv[i], s, s6);
		}
	}

	if (s != -1)
		close(s);
	if (s6 != -1)
		close(s6);

	exit (0);
}