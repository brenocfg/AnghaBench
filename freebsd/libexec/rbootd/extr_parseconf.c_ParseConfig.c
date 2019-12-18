#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/ ** files; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 scalar_t__ BootAny ; 
 int /*<<< orphan*/ ** BootFiles ; 
 int C_LINELEN ; 
 int C_MAXFILE ; 
 TYPE_1__* Clients ; 
 int /*<<< orphan*/  ConfigFile ; 
 int /*<<< orphan*/  FreeClient (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeClients () ; 
 int /*<<< orphan*/  GETSTR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 TYPE_1__* NewClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseAddr (char*) ; 
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ STREQN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int,...) ; 

int
ParseConfig(void)
{
	FILE *fp;
	CLIENT *client;
	u_int8_t *addr;
	char line[C_LINELEN];
	char *cp, *bcp;
	int i, j;
	int omask, linecnt = 0;

	if (BootAny)				/* ignore config file */
		return(1);

	FreeClients();				/* delete old list of clients */

	if ((fp = fopen(ConfigFile, "r")) == NULL) {
		syslog(LOG_ERR, "ParseConfig: can't open config file (%s)",
		       ConfigFile);
		return(0);
	}

	/*
	 *  We've got to block SIGHUP to prevent reconfiguration while
	 *  dealing with the linked list of Clients.  This can be done
	 *  when actually linking the new client into the list, but
	 *  this could have unexpected results if the server was HUP'd
	 *  whilst reconfiguring.  Hence, it is done here.
	 */
	omask = sigblock(sigmask(SIGHUP));

	/*
	 *  GETSTR positions `bcp' at the start of the current token,
	 *  and null terminates it.  `cp' is positioned at the start
	 *  of the next token.  spaces & commas are separators.
	 */
#define GETSTR	while (isspace(*cp) || *cp == ',') cp++;	\
		bcp = cp;					\
		while (*cp && *cp!=',' && !isspace(*cp)) cp++;	\
		if (*cp) *cp++ = '\0'

	/*
	 *  For each line, parse it into a new CLIENT struct.
	 */
	while (fgets(line, C_LINELEN, fp) != NULL) {
		linecnt++;				/* line counter */

		if (*line == '\0' || *line == '#')	/* ignore comment */
			continue;

		if ((cp = strchr(line,'#')) != NULL)	/* trash comments */
			*cp = '\0';

		cp = line;				/* init `cp' */
		GETSTR;					/* get RMP addr */
		if (bcp == cp)				/* all delimiters */
			continue;

		/*
		 *  Get an RMP address from a string.  Abort on failure.
		 */
		if ((addr = ParseAddr(bcp)) == NULL) {
			syslog(LOG_ERR,
			       "ParseConfig: line %d: can't parse <%s>",
			       linecnt, bcp);
			continue;
		}

		if ((client = NewClient(addr)) == NULL)	/* alloc new client */
			continue;

		GETSTR;					/* get first file */

		/*
		 *  If no boot files are spec'd, use the default list.
		 *  Otherwise, validate each file (`bcp') against the
		 *  list of boot-able files.
		 */
		i = 0;
		if (bcp == cp)				/* no files spec'd */
			for (; i < C_MAXFILE && BootFiles[i] != NULL; i++)
				client->files[i] = BootFiles[i];
		else {
			do {
				/*
				 *  For each boot file spec'd, make sure it's
				 *  in our list.  If so, include a pointer to
				 *  it in the CLIENT's list of boot files.
				 */
				for (j = 0; ; j++) {
					if (j==C_MAXFILE||BootFiles[j]==NULL) {
						syslog(LOG_ERR, "ParseConfig: line %d: no boot file (%s)",
						       linecnt, bcp);
						break;
					}
					if (STREQN(BootFiles[j], bcp)) {
						if (i < C_MAXFILE)
							client->files[i++] =
							    BootFiles[j];
						else
							syslog(LOG_ERR, "ParseConfig: line %d: too many boot files (%s)",
							       linecnt, bcp);
						break;
					}
				}
				GETSTR;			/* get next file */
			} while (bcp != cp);

			/*
			 *  Restricted list of boot files were spec'd,
			 *  however, none of them were found.  Since we
			 *  apparently can't let them boot "just anything",
			 *  the entire record is invalidated.
			 */
			if (i == 0) {
				FreeClient(client);
				continue;
			}
		}

		/*
		 *  Link this client into the linked list of clients.
		 *  SIGHUP has already been blocked.
		 */
		if (Clients)
			client->next = Clients;
		Clients = client;
	}

	(void) fclose(fp);				/* close config file */

	(void) sigsetmask(omask);			/* reset signal mask */

	return(1);					/* return success */
}