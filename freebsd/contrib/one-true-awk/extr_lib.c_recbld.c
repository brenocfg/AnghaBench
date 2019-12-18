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
struct TYPE_5__ {char* sval; int tval; } ;

/* Variables and functions */
 int DONTFREE ; 
 int /*<<< orphan*/  FATAL (char*,char*) ; 
 int* NF ; 
 int REC ; 
 int STR ; 
 int /*<<< orphan*/  adjbuf (char**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char**,char*) ; 
 int donerec ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 TYPE_1__** fldtab ; 
 scalar_t__ freeable (TYPE_1__*) ; 
 char* getsval (TYPE_1__*) ; 
 int /*<<< orphan*/  inputFS ; 
 TYPE_1__* ofsloc ; 
 char* record ; 
 int /*<<< orphan*/  recsize ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void recbld(void)	/* create $0 from $1..$NF if necessary */
{
	int i;
	char *r, *p;
	char *sep = getsval(ofsloc);

	if (donerec == 1)
		return;
	r = record;
	for (i = 1; i <= *NF; i++) {
		p = getsval(fldtab[i]);
		if (!adjbuf(&record, &recsize, 1+strlen(p)+r-record, recsize, &r, "recbld 1"))
			FATAL("created $0 `%.30s...' too long", record);
		while ((*r = *p++) != 0)
			r++;
		if (i < *NF) {
			if (!adjbuf(&record, &recsize, 2+strlen(sep)+r-record, recsize, &r, "recbld 2"))
				FATAL("created $0 `%.30s...' too long", record);
			for (p = sep; (*r = *p++) != 0; )
				r++;
		}
	}
	if (!adjbuf(&record, &recsize, 2+r-record, recsize, &r, "recbld 3"))
		FATAL("built giant record `%.30s...'", record);
	*r = '\0';
	   dprintf( ("in recbld inputFS=%s, fldtab[0]=%p\n", inputFS, (void*)fldtab[0]) );

	if (freeable(fldtab[0]))
		xfree(fldtab[0]->sval);
	fldtab[0]->tval = REC | STR | DONTFREE;
	fldtab[0]->sval = record;

	   dprintf( ("in recbld inputFS=%s, fldtab[0]=%p\n", inputFS, (void*)fldtab[0]) );
	   dprintf( ("recbld = |%s|\n", record) );
	donerec = 1;
}