#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* nextfu; struct TYPE_5__* nextfs; } ;
struct TYPE_4__ {int reps; int /*<<< orphan*/  fmt; void* bcnt; int /*<<< orphan*/  flags; struct TYPE_4__* nextfu; } ;
typedef  TYPE_1__ FU ;
typedef  TYPE_2__ FS ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETREP ; 
 void* atoi (unsigned char const*) ; 
 int /*<<< orphan*/  badfmt (char const*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  escape (int /*<<< orphan*/ ) ; 
 TYPE_2__* fshead ; 
 scalar_t__ isdigit (unsigned char const) ; 
 scalar_t__ isspace (unsigned char const) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 

void
add(const char *fmt)
{
	unsigned const char *p, *savep;
	static FS **nextfs;
	FS *tfs;
	FU *tfu, **nextfu;

	/* start new linked list of format units */
	if ((tfs = calloc(1, sizeof(FS))) == NULL)
		err(1, NULL);
	if (!fshead)
		fshead = tfs;
	else
		*nextfs = tfs;
	nextfs = &tfs->nextfs;
	nextfu = &tfs->nextfu;

	/* take the format string and break it up into format units */
	for (p = fmt;;) {
		/* skip leading white space */
		for (; isspace(*p); ++p);
		if (!*p)
			break;

		/* allocate a new format unit and link it in */
		if ((tfu = calloc(1, sizeof(FU))) == NULL)
			err(1, NULL);
		*nextfu = tfu;
		nextfu = &tfu->nextfu;
		tfu->reps = 1;

		/* if leading digit, repetition count */
		if (isdigit(*p)) {
			for (savep = p; isdigit(*p); ++p);
			if (!isspace(*p) && *p != '/')
				badfmt(fmt);
			/* may overwrite either white space or slash */
			tfu->reps = atoi(savep);
			tfu->flags = F_SETREP;
			/* skip trailing white space */
			for (++p; isspace(*p); ++p);
		}

		/* skip slash and trailing white space */
		if (*p == '/')
			while (isspace(*++p));

		/* byte count */
		if (isdigit(*p)) {
			for (savep = p; isdigit(*p); ++p);
			if (!isspace(*p))
				badfmt(fmt);
			tfu->bcnt = atoi(savep);
			/* skip trailing white space */
			for (++p; isspace(*p); ++p);
		}

		/* format */
		if (*p != '"')
			badfmt(fmt);
		for (savep = ++p; *p != '"';)
			if (*p++ == 0)
				badfmt(fmt);
		if (!(tfu->fmt = malloc(p - savep + 1)))
			err(1, NULL);
		(void) strlcpy(tfu->fmt, savep, p - savep + 1);
		escape(tfu->fmt);
		p++;
	}
}