#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  pbuf ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {scalar_t__ (* close ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ DB ;

/* Variables and functions */
 size_t BFRAG ; 
 int BUFSIZ ; 
 int /*<<< orphan*/  DB_HASH ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_RECURSION ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _POSIX_PATH_MAX ; 
 int /*<<< orphan*/  _close (int) ; 
 int _open (char*,int,int /*<<< orphan*/ ) ; 
 int _read (int,char*,int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int cdbget (TYPE_1__*,char**,char const*) ; 
 char* cgetcap (char*,char*,char) ; 
 scalar_t__ cgetmatch (char*,char const*) ; 
 TYPE_1__* dbopen (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  nfcmp (char*,char*) ; 
 char* reallocf (char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 
 scalar_t__ stub2 (TYPE_1__*) ; 
 char* toprec ; 
 size_t topreclen ; 

__attribute__((used)) static int
getent(char **cap, u_int *len, char **db_array, int fd, const char *name,
    int depth, char *nfield)
{
	DB *capdbp;
	char *r_end, *rp, **db_p;
	int myfd, eof, foundit, retval;
	char *record, *cbuf;
	int tc_not_resolved;
	char pbuf[_POSIX_PATH_MAX];

	/*
	 * Return with ``loop detected'' error if we've recursed more than
	 * MAX_RECURSION times.
	 */
	if (depth > MAX_RECURSION)
		return (-3);

	/*
	 * Check if we have a top record from cgetset().
         */
	if (depth == 0 && toprec != NULL && cgetmatch(toprec, name) == 0) {
		if ((record = malloc (topreclen + BFRAG)) == NULL) {
			errno = ENOMEM;
			return (-2);
		}
		(void)strcpy(record, toprec);
		myfd = 0;
		db_p = db_array;
		rp = record + topreclen + 1;
		r_end = rp + BFRAG;
		goto tc_exp;
	}
	/*
	 * Allocate first chunk of memory.
	 */
	if ((record = malloc(BFRAG)) == NULL) {
		errno = ENOMEM;
		return (-2);
	}
	r_end = record + BFRAG;
	foundit = 0;
	/*
	 * Loop through database array until finding the record.
	 */

	for (db_p = db_array; *db_p != NULL; db_p++) {
		eof = 0;

		/*
		 * Open database if not already open.
		 */

		if (fd >= 0) {
			(void)lseek(fd, (off_t)0, SEEK_SET);
			myfd = 0;
		} else {
			(void)snprintf(pbuf, sizeof(pbuf), "%s.db", *db_p);
			if ((capdbp = dbopen(pbuf, O_RDONLY, 0, DB_HASH, 0))
			     != NULL) {
				free(record);
				retval = cdbget(capdbp, &record, name);
				if (retval < 0) {
					/* no record available */
					(void)capdbp->close(capdbp);
					return (retval);
				}
				/* save the data; close frees it */
				cbuf = strdup(record);
				if (capdbp->close(capdbp) < 0) {
					free(cbuf);
					return (-2);
				}
				if (cbuf == NULL) {
					errno = ENOMEM;
					return (-2);
				}
				*len = strlen(cbuf);
				*cap = cbuf;
				return (retval);
			} else {
				fd = _open(*db_p, O_RDONLY | O_CLOEXEC, 0);
				if (fd < 0)
					continue;
				myfd = 1;
			}
		}
		/*
		 * Find the requested capability record ...
		 */
		{
		char buf[BUFSIZ];
		char *b_end, *bp;
		int c;

		/*
		 * Loop invariants:
		 *	There is always room for one more character in record.
		 *	R_end always points just past end of record.
		 *	Rp always points just past last character in record.
		 *	B_end always points just past last character in buf.
		 *	Bp always points at next character in buf.
		 */
		b_end = buf;
		bp = buf;
		for (;;) {

			/*
			 * Read in a line implementing (\, newline)
			 * line continuation.
			 */
			rp = record;
			for (;;) {
				if (bp >= b_end) {
					int n;

					n = _read(fd, buf, sizeof(buf));
					if (n <= 0) {
						if (myfd)
							(void)_close(fd);
						if (n < 0) {
							free(record);
							return (-2);
						} else {
							fd = -1;
							eof = 1;
							break;
						}
					}
					b_end = buf+n;
					bp = buf;
				}

				c = *bp++;
				if (c == '\n') {
					if (rp > record && *(rp-1) == '\\') {
						rp--;
						continue;
					} else
						break;
				}
				*rp++ = c;

				/*
				 * Enforce loop invariant: if no room
				 * left in record buffer, try to get
				 * some more.
				 */
				if (rp >= r_end) {
					u_int pos;
					size_t newsize;

					pos = rp - record;
					newsize = r_end - record + BFRAG;
					record = reallocf(record, newsize);
					if (record == NULL) {
						errno = ENOMEM;
						if (myfd)
							(void)_close(fd);
						return (-2);
					}
					r_end = record + newsize;
					rp = record + pos;
				}
			}
				/* loop invariant let's us do this */
			*rp++ = '\0';

			/*
			 * If encountered eof check next file.
			 */
			if (eof)
				break;

			/*
			 * Toss blank lines and comments.
			 */
			if (*record == '\0' || *record == '#')
				continue;

			/*
			 * See if this is the record we want ...
			 */
			if (cgetmatch(record, name) == 0) {
				if (nfield == NULL || !nfcmp(nfield, record)) {
					foundit = 1;
					break;	/* found it! */
				}
			}
		}
	}
		if (foundit)
			break;
	}

	if (!foundit) {
		free(record);
		return (-1);
	}

	/*
	 * Got the capability record, but now we have to expand all tc=name
	 * references in it ...
	 */
tc_exp:	{
		char *newicap, *s;
		int newilen;
		u_int ilen;
		int diff, iret, tclen;
		char *icap, *scan, *tc, *tcstart, *tcend;

		/*
		 * Loop invariants:
		 *	There is room for one more character in record.
		 *	R_end points just past end of record.
		 *	Rp points just past last character in record.
		 *	Scan points at remainder of record that needs to be
		 *	scanned for tc=name constructs.
		 */
		scan = record;
		tc_not_resolved = 0;
		for (;;) {
			if ((tc = cgetcap(scan, "tc", '=')) == NULL)
				break;

			/*
			 * Find end of tc=name and stomp on the trailing `:'
			 * (if present) so we can use it to call ourselves.
			 */
			s = tc;
			for (;;)
				if (*s == '\0')
					break;
				else
					if (*s++ == ':') {
						*(s - 1) = '\0';
						break;
					}
			tcstart = tc - 3;
			tclen = s - tcstart;
			tcend = s;

			iret = getent(&icap, &ilen, db_p, fd, tc, depth+1,
				      NULL);
			newicap = icap;		/* Put into a register. */
			newilen = ilen;
			if (iret != 0) {
				/* an error */
				if (iret < -1) {
					if (myfd)
						(void)_close(fd);
					free(record);
					return (iret);
				}
				if (iret == 1)
					tc_not_resolved = 1;
				/* couldn't resolve tc */
				if (iret == -1) {
					*(s - 1) = ':';
					scan = s - 1;
					tc_not_resolved = 1;
					continue;

				}
			}
			/* not interested in name field of tc'ed record */
			s = newicap;
			for (;;)
				if (*s == '\0')
					break;
				else
					if (*s++ == ':')
						break;
			newilen -= s - newicap;
			newicap = s;

			/* make sure interpolated record is `:'-terminated */
			s += newilen;
			if (*(s-1) != ':') {
				*s = ':';	/* overwrite NUL with : */
				newilen++;
			}

			/*
			 * Make sure there's enough room to insert the
			 * new record.
			 */
			diff = newilen - tclen;
			if (diff >= r_end - rp) {
				u_int pos, tcpos, tcposend;
				size_t newsize;

				pos = rp - record;
				newsize = r_end - record + diff + BFRAG;
				tcpos = tcstart - record;
				tcposend = tcend - record;
				record = reallocf(record, newsize);
				if (record == NULL) {
					errno = ENOMEM;
					if (myfd)
						(void)_close(fd);
					free(icap);
					return (-2);
				}
				r_end = record + newsize;
				rp = record + pos;
				tcstart = record + tcpos;
				tcend = record + tcposend;
			}

			/*
			 * Insert tc'ed record into our record.
			 */
			s = tcstart + newilen;
			bcopy(tcend, s, rp - tcend);
			bcopy(newicap, tcstart, newilen);
			rp += diff;
			free(icap);

			/*
			 * Start scan on `:' so next cgetcap works properly
			 * (cgetcap always skips first field).
			 */
			scan = s-1;
		}

	}
	/*
	 * Close file (if we opened it), give back any extra memory, and
	 * return capability, length and success.
	 */
	if (myfd)
		(void)_close(fd);
	*len = rp - record - 1;	/* don't count NUL */
	if (r_end > rp)
		if ((record =
		     reallocf(record, (size_t)(rp - record))) == NULL) {
			errno = ENOMEM;
			return (-2);
		}

	*cap = record;
	if (tc_not_resolved)
		return (1);
	return (0);
}