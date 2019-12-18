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
struct TYPE_2__ {char* m_mode; int /*<<< orphan*/ * m_name; } ;

/* Variables and functions */
 int ARG_MAX ; 
 int MAXLINE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeargv (char*) ; 
 int /*<<< orphan*/  margc ; 
 int /*<<< orphan*/  margv ; 
 char* mode ; 
 TYPE_1__* modes ; 
 int /*<<< orphan*/  setpeer0 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  settftpmode (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
urihandling(char *URI)
{
	char	uri[ARG_MAX];
	char	*host = NULL;
	char	*path = NULL;
	char	*opts = NULL;
	const char *tmode = "octet";
	char	*s;
	char	line[MAXLINE];
	int	i;

	strlcpy(uri, URI, ARG_MAX);
	host = uri + 7;

	if ((s = strchr(host, '/')) == NULL) {
		fprintf(stderr,
		    "Invalid URI: Couldn't find / after hostname\n");
		exit(1);
	}
	*s = '\0';
	path = s + 1;

	if ((s = strchr(path, ';')) != NULL) {
		*s = '\0';
		opts = s + 1;

		if (strncmp(opts, "mode=", 5) == 0) {
			tmode = opts;
			tmode += 5;

			for (i = 0; modes[i].m_name != NULL; i++) {
				if (strcmp(modes[i].m_name, tmode) == 0)
					break;
			}
			if (modes[i].m_name == NULL) {
				fprintf(stderr, "Invalid mode: '%s'\n", mode);
				exit(1);
			}
			settftpmode(modes[i].m_mode);
		}
	} else {
		settftpmode("octet");
	}

	setpeer0(host, NULL);

	sprintf(line, "get %s", path);
	makeargv(line);
	get(margc, margv);
}