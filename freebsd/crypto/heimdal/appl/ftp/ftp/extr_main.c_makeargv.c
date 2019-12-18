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
 int /*<<< orphan*/  argbase ; 
 int /*<<< orphan*/  argbuf ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  line ; 
 scalar_t__ malloc (int) ; 
 int margc ; 
 char** margv ; 
 int margvlen ; 
 scalar_t__ realloc (char**,int) ; 
 scalar_t__ slrflag ; 
 int /*<<< orphan*/ * slurpstring () ; 
 int /*<<< orphan*/  stringbase ; 

void
makeargv(void)
{
	char **argp;

	argp = margv;
	stringbase = line;		/* scan from first of buffer */
	argbase = argbuf;		/* store from first of buffer */
	slrflag = 0;
	for (margc = 0; ; margc++) {
		/* Expand array if necessary */
		if (margc == margvlen) {
			int i;

			margv = (margvlen == 0)
				? (char **)malloc(20 * sizeof(char *))
				: (char **)realloc(margv,
					(margvlen + 20)*sizeof(char *));
			if (margv == NULL)
				errx(1, "cannot realloc argv array");
			for(i = margvlen; i < margvlen + 20; ++i)
				margv[i] = NULL;
			margvlen += 20;
			argp = margv + margc;
		}

		if ((*argp++ = slurpstring()) == NULL)
			break;
	}

}