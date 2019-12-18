#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int numPcdacValues; } ;
struct TYPE_5__ {TYPE_1__* pDataPerChannel; } ;
struct TYPE_4__ {int numPdGains; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int MAXID ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int bol ; 
 int curchan ; 
 int curctl ; 
 int curlpdgain ; 
 int curmode ; 
 int curpcdac ; 
 int curpdgain ; 
 int /*<<< orphan*/  eevar (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmode (int /*<<< orphan*/ *,char*) ; 
 int lineno ; 
 int nextctl (int) ; 
 int numChannels ; 
 TYPE_3__* pDataPerChannel ; 
 TYPE_2__* pRaw ; 
 int pdgain (int) ; 
 int /*<<< orphan*/  skipto (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skipws (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int token (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  warnx (char*,int,char*) ; 

__attribute__((used)) static void
parseTemplate(FILE *ftemplate, FILE *fd)
{
	int c, i;
	char id[MAXID];
	long forchan, forpdgain, forctl, forpcdac;

	lineno = 1;
	bol = 1;
	while ((c = getc(ftemplate)) != EOF) {
		if (c == '#') {			/* comment */
	skiptoeol:
			while ((c = getc(ftemplate)) != EOF && c != '\n')
				;
			if (c == EOF)
				return;
			lineno++;
			bol = 1;
			continue;
		}
		if (c == '.' && bol) {		/* .directive */
			if (token(ftemplate, id, MAXID, ".directive") == EOF)
				return;
			/* process directive */
			if (strcasecmp(id, "ifmode") == 0) {
				skipws(ftemplate);
				if (token(ftemplate, id, MAXID, "id") == EOF)
					return;
				ifmode(ftemplate, id);
			} else if (strcasecmp(id, "endmode") == 0) {
				/* XXX free malloc'd indirect data */
				curmode = -1;	/* NB: undefined */
			} else if (strcasecmp(id, "forchan") == 0) {
				forchan = ftell(ftemplate) - sizeof("forchan");
				if (curchan == -1)
					curchan = 0;
			} else if (strcasecmp(id, "endforchan") == 0) {
				if (++curchan < numChannels)
					fseek(ftemplate, forchan, SEEK_SET);
				else
					curchan = -1;
			} else if (strcasecmp(id, "ifpdgain") == 0) {
				skipws(ftemplate);
				if (token(ftemplate, id, MAXID, "pdgain") == EOF)
					return;
				curlpdgain = strtoul(id, NULL, 0);
				if (curlpdgain >= pRaw->pDataPerChannel[curchan].numPdGains) {
					skipto(ftemplate, "endpdgain");
					curlpdgain = -1;
				} else
					curpdgain = pdgain(curlpdgain);
			} else if (strcasecmp(id, "endpdgain") == 0) {
				curlpdgain = curpdgain = -1;
			} else if (strcasecmp(id, "forpdgain") == 0) {
				forpdgain = ftell(ftemplate) - sizeof("forpdgain");
				if (curlpdgain == -1) {
					skipws(ftemplate);
					if (token(ftemplate, id, MAXID, "pdgain") == EOF)
						return;
					curlpdgain = strtoul(id, NULL, 0);
					if (curlpdgain >= pRaw->pDataPerChannel[curchan].numPdGains) {
						skipto(ftemplate, "endforpdgain");
						curlpdgain = -1;
					} else
						curpdgain = pdgain(curlpdgain);
				}
			} else if (strcasecmp(id, "endforpdgain") == 0) {
				if (++curpdgain < pRaw->pDataPerChannel[curchan].numPdGains)
					fseek(ftemplate, forpdgain, SEEK_SET);
				else
					curpdgain = -1;
			} else if (strcasecmp(id, "forpcdac") == 0) {
				forpcdac = ftell(ftemplate) - sizeof("forpcdac");
				if (curpcdac == -1)
					curpcdac = 0;
			} else if (strcasecmp(id, "endforpcdac") == 0) {
				if (++curpcdac < pDataPerChannel[0].numPcdacValues)
					fseek(ftemplate, forpcdac, SEEK_SET);
				else
					curpcdac = -1;
			} else if (strcasecmp(id, "forctl") == 0) {
				forctl = ftell(ftemplate) - sizeof("forchan");
				if (curctl == -1)
					curctl = nextctl(0);
			} else if (strcasecmp(id, "endforctl") == 0) {
				curctl = nextctl(curctl+1);
				if (curctl != -1)
					fseek(ftemplate, forctl, SEEK_SET);
			} else {
				warnx("line %d, unknown directive %s ignored",
				    lineno, id);
			}
			goto skiptoeol;
		}
		if (c == '$') {			/* $variable reference */
			if (token(ftemplate, id, MAXID, "$var") == EOF)
				return;
			/* XXX not valid if variable depends on curmode */
			eevar(fd, id);
			continue;
		}
		if (c == '\\') {		/* escape next character */
			c = getc(ftemplate);
			if (c == EOF)
				return;
		}
		fputc(c, fd);
		bol = (c == '\n');
		if (bol)
			lineno++;
	}
}