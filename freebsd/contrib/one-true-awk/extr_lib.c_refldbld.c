#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int initstat; } ;
typedef  TYPE_1__ fa ;
struct TYPE_7__ {char* sval; int tval; } ;

/* Variables and functions */
 int DONTFREE ; 
 int /*<<< orphan*/  FATAL (char*,int) ; 
 int FLD ; 
 int STR ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 char* fields ; 
 int fieldssize ; 
 TYPE_4__** fldtab ; 
 scalar_t__ freeable (TYPE_4__*) ; 
 int /*<<< orphan*/  growfldtab (int) ; 
 TYPE_1__* makedfa (char const*,int) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ nematch (TYPE_1__*,char const*) ; 
 int nfields ; 
 char const* patbeg ; 
 int patlen ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  xfree (char*) ; 

int refldbld(const char *rec, const char *fs)	/* build fields from reg expr in FS */
{
	/* this relies on having fields[] the same length as $0 */
	/* the fields are all stored in this one array with \0's */
	char *fr;
	int i, tempstat, n;
	fa *pfa;

	n = strlen(rec);
	if (n > fieldssize) {
		xfree(fields);
		if ((fields = (char *) malloc(n+1)) == NULL)
			FATAL("out of space for fields in refldbld %d", n);
		fieldssize = n;
	}
	fr = fields;
	*fr = '\0';
	if (*rec == '\0')
		return 0;
	pfa = makedfa(fs, 1);
	   dprintf( ("into refldbld, rec = <%s>, pat = <%s>\n", rec, fs) );
	tempstat = pfa->initstat;
	for (i = 1; ; i++) {
		if (i > nfields)
			growfldtab(i);
		if (freeable(fldtab[i]))
			xfree(fldtab[i]->sval);
		fldtab[i]->tval = FLD | STR | DONTFREE;
		fldtab[i]->sval = fr;
		   dprintf( ("refldbld: i=%d\n", i) );
		if (nematch(pfa, rec)) {
			pfa->initstat = 2;	/* horrible coupling to b.c */
			   dprintf( ("match %s (%d chars)\n", patbeg, patlen) );
			strncpy(fr, rec, patbeg-rec);
			fr += patbeg - rec + 1;
			*(fr-1) = '\0';
			rec = patbeg + patlen;
		} else {
			   dprintf( ("no match %s\n", rec) );
			strcpy(fr, rec);
			pfa->initstat = tempstat;
			break;
		}
	}
	return i;		
}