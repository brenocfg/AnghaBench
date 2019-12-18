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
typedef  int /*<<< orphan*/  u_short ;
struct parse {char* keyword; TYPE_1__* argval; } ;
struct TYPE_2__ {char* string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_OP_CONFIGURE ; 
 int debug ; 
 int doquery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*,int /*<<< orphan*/ *,size_t*,char const**) ; 
 char* emalloc (size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ interactive ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int strlen (char const*) ; 

__attribute__((used)) static void 
config (
	struct parse *pcmd,
	FILE *fp
	)
{
	const char *cfgcmd;
	u_short rstatus;
	size_t rsize;
	const char *rdata;
	char *resp;
	int res;
	int col;
	int i;

	cfgcmd = pcmd->argval[0].string;

	if (debug > 2)
		fprintf(stderr, 
			"In Config\n"
			"Keyword = %s\n"
			"Command = %s\n", pcmd->keyword, cfgcmd);

	res = doquery(CTL_OP_CONFIGURE, 0, 1,
		      strlen(cfgcmd), cfgcmd,
		      &rstatus, &rsize, &rdata);

	if (res != 0)
		return;

	if (rsize > 0 && '\n' == rdata[rsize - 1])
		rsize--;

	resp = emalloc(rsize + 1);
	memcpy(resp, rdata, rsize);
	resp[rsize] = '\0';

	col = -1;
	if (1 == sscanf(resp, "column %d syntax error", &col)
	    && col >= 0 && (size_t)col <= strlen(cfgcmd) + 1) {
		if (interactive)
			fputs("             *", stdout); /* "ntpq> :config " */
		else
			printf("%s\n", cfgcmd);
		for (i = 0; i < col; i++)
			fputc('_', stdout);
		fputs("^\n", stdout);
	}
	printf("%s\n", resp);
	free(resp);
}