#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int recno_t ;
struct TYPE_10__ {int (* put ) (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {char* data; size_t size; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 scalar_t__ MAX (int,size_t) ; 
 scalar_t__ MIN (size_t,int) ; 
 char RECOK ; 
 int /*<<< orphan*/  R_NOOVERWRITE ; 
 char SHADOW ; 
 char TCERR ; 
 TYPE_2__* capdbp ; 
 int cgetnext (char**,char**) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 char* realloc (char*,size_t) ; 
 char* strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int stub1 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_2__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warnx (char*,int,char*) ; 

__attribute__((used)) static void
db_build(char **ifiles)
{
	DBT key, data;
	recno_t reccnt;
	size_t len, bplen;
	int st;
	char *bp, *p, *t;

	data.data = NULL;
	key.data = NULL;
	for (reccnt = 0, bplen = 0; (st = cgetnext(&bp, ifiles)) > 0;) {

		/*
		 * Allocate enough memory to store record, terminating
		 * NULL and one extra byte.
		 */
		len = strlen(bp);
		if (bplen <= len + 2) {
			bplen += MAX(256, len + 2);
			if ((data.data = realloc(data.data, bplen)) == NULL)
				errx(1, "malloc failed");
		}

		/* Find the end of the name field. */
		if ((p = strchr(bp, ':')) == NULL) {
			warnx("no name field: %.*s", (int)MIN(len, 20), bp);
			continue;
		}

		/* First byte of stored record indicates status. */
		switch(st) {
		case 1:
			((char *)(data.data))[0] = RECOK;
			break;
		case 2:
			((char *)(data.data))[0] = TCERR;
			warnx("record not tc expanded: %.*s", (int)(p - bp),
			    bp);
			break;
		}

		/* Create the stored record. */
		memmove(&((u_char *)(data.data))[1], bp, len + 1);
		data.size = len + 2;

		/* Store the record under the name field. */
		key.data = bp;
		key.size = p - bp;

		switch(capdbp->put(capdbp, &key, &data, R_NOOVERWRITE)) {
		case -1:
			err(1, "put");
			/* NOTREACHED */
		case 1:
			warnx("ignored duplicate: %.*s",
			    (int)key.size, (char *)key.data);
			continue;
		}
		++reccnt;

		/* If only one name, ignore the rest. */
		*p = '\0';
		if (strchr(bp, '|') == NULL)
			continue;
		*p = ':';

		/* The rest of the names reference the entire name. */
		((char *)(data.data))[0] = SHADOW;
		memmove(&((u_char *)(data.data))[1], key.data, key.size);
		data.size = key.size + 1;

		/* Store references for other names. */
		for (p = t = bp;; ++p) {
			if (p > t && (*p == ':' || *p == '|')) {
				key.size = p - t;
				key.data = t;
				switch(capdbp->put(capdbp,
				    &key, &data, R_NOOVERWRITE)) {
				case -1:
					err(1, "put");
					/* NOTREACHED */
				case 1:
					warnx("ignored duplicate: %.*s",
					    (int)key.size, (char *)key.data);
				}
				t = p + 1;
			}
			if (*p == ':')
				break;
		}
	}

	switch(st) {
	case -1:
		err(1, "file argument");
		/* NOTREACHED */
	case -2:
		errx(1, "potential reference loop detected");
		/* NOTREACHED */
	}

	if (verbose)
		(void)printf("cap_mkdb: %d capability records\n", reccnt);
}