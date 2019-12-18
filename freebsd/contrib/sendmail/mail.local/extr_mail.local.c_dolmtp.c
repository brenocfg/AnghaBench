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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 int /*<<< orphan*/  EightBitMime ; 
 int HoldErrs ; 
 int RCPT_GROW ; 
 scalar_t__ REALLOC (char*,int) ; 
 int StripRcptDomain ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  deliver (int,char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_error () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int /*<<< orphan*/  mailerr (char*,char*,...) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 char* parseaddr (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* process_recipient (char*) ; 
 int /*<<< orphan*/  sm_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  sm_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  sm_strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int store (char*,int*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

void
dolmtp()
{
	char *return_path = NULL;
	char **rcpt_addr = NULL;
	int rcpt_num = 0;
	int rcpt_alloc = 0;
	bool gotlhlo = false;
	char *err;
	int msgfd;
	char *p;
	int i;
	char myhostname[1024];
	char buf[4096];

	memset(myhostname, '\0', sizeof myhostname);
	(void) gethostname(myhostname, sizeof myhostname - 1);
	if (myhostname[0] == '\0')
		sm_strlcpy(myhostname, "localhost", sizeof myhostname);

	printf("220 %s LMTP ready\r\n", myhostname);
	for (;;)
	{
		(void) fflush(stdout);
		if (fgets(buf, sizeof(buf) - 1, stdin) == NULL)
			sm_exit(EX_OK);
		p = buf + strlen(buf) - 1;
		if (p >= buf && *p == '\n')
			*p-- = '\0';
		if (p >= buf && *p == '\r')
			*p-- = '\0';

		switch (buf[0])
		{
		  case 'd':
		  case 'D':
			if (sm_strcasecmp(buf, "data") == 0)
			{
				bool inbody = false;

				if (rcpt_num == 0)
				{
					mailerr("503 5.5.1", "No recipients");
					continue;
				}
				HoldErrs = true;
				msgfd = store(return_path, &inbody);
				HoldErrs = false;
				if (msgfd < 0 && !inbody)
				{
					flush_error();
					continue;
				}

				for (i = 0; i < rcpt_num; i++)
				{
					if (msgfd < 0)
					{
						/* print error for rcpt */
						flush_error();
						continue;
					}
					p = strchr(rcpt_addr[i], '+');
					if (p != NULL)
						*p = '\0';
					deliver(msgfd, rcpt_addr[i]);
				}
				if (msgfd >= 0)
					(void) close(msgfd);
				goto rset;
			}
			goto syntaxerr;
			/* NOTREACHED */
			break;

		  case 'l':
		  case 'L':
			if (sm_strncasecmp(buf, "lhlo ", 5) == 0)
			{
				/* check for duplicate per RFC 1651 4.2 */
				if (gotlhlo)
				{
					mailerr("503", "%s Duplicate LHLO",
					       myhostname);
					continue;
				}
				gotlhlo = true;
				printf("250-%s\r\n", myhostname);
				if (EightBitMime)
					printf("250-8BITMIME\r\n");
				printf("250-ENHANCEDSTATUSCODES\r\n");
				printf("250 PIPELINING\r\n");
				continue;
			}
			goto syntaxerr;
			/* NOTREACHED */
			break;

		  case 'm':
		  case 'M':
			if (sm_strncasecmp(buf, "mail ", 5) == 0)
			{
				if (return_path != NULL)
				{
					mailerr("503 5.5.1",
						"Nested MAIL command");
					continue;
				}
				if (sm_strncasecmp(buf + 5, "from:", 5) != 0 ||
				    ((return_path = parseaddr(buf + 10,
							      false)) == NULL))
				{
					mailerr("501 5.5.4",
						"Syntax error in parameters");
					continue;
				}
				printf("250 2.5.0 Ok\r\n");
				continue;
			}
			goto syntaxerr;
			/* NOTREACHED */
			break;

		  case 'n':
		  case 'N':
			if (sm_strcasecmp(buf, "noop") == 0)
			{
				printf("250 2.0.0 Ok\r\n");
				continue;
			}
			goto syntaxerr;
			/* NOTREACHED */
			break;

		  case 'q':
		  case 'Q':
			if (sm_strcasecmp(buf, "quit") == 0)
			{
				printf("221 2.0.0 Bye\r\n");
				sm_exit(EX_OK);
			}
			goto syntaxerr;
			/* NOTREACHED */
			break;

		  case 'r':
		  case 'R':
			if (sm_strncasecmp(buf, "rcpt ", 5) == 0)
			{
				if (return_path == NULL)
				{
					mailerr("503 5.5.1",
						"Need MAIL command");
					continue;
				}
				if (rcpt_num >= rcpt_alloc)
				{
					rcpt_alloc += RCPT_GROW;
					rcpt_addr = (char **)
						REALLOC((char *) rcpt_addr,
							rcpt_alloc *
							sizeof(char **));
					if (rcpt_addr == NULL)
					{
						mailerr("421 4.3.0",
							"Memory exhausted");
						sm_exit(EX_TEMPFAIL);
					}
				}
				if (sm_strncasecmp(buf + 5, "to:", 3) != 0 ||
				    ((rcpt_addr[rcpt_num] = parseaddr(buf + 8,
								      StripRcptDomain)) == NULL))
				{
					mailerr("501 5.5.4",
						"Syntax error in parameters");
					continue;
				}
				err = process_recipient(rcpt_addr[rcpt_num]);
				if (err != NULL)
				{
					mailerr(NULL, "%s", err);
					continue;
				}
				rcpt_num++;
				printf("250 2.1.5 Ok\r\n");
				continue;
			}
			else if (sm_strcasecmp(buf, "rset") == 0)
			{
				printf("250 2.0.0 Ok\r\n");

rset:
				while (rcpt_num > 0)
					free(rcpt_addr[--rcpt_num]);
				if (return_path != NULL)
					free(return_path);
				return_path = NULL;
				continue;
			}
			goto syntaxerr;
			/* NOTREACHED */
			break;

		  case 'v':
		  case 'V':
			if (sm_strncasecmp(buf, "vrfy ", 5) == 0)
			{
				printf("252 2.3.3 Try RCPT to attempt delivery\r\n");
				continue;
			}
			goto syntaxerr;
			/* NOTREACHED */
			break;

		  default:
  syntaxerr:
			mailerr("500 5.5.2", "Syntax error");
			continue;
			/* NOTREACHED */
			break;
		}
	}
}