#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  recno_t ;
typedef  int /*<<< orphan*/  recno ;
typedef  enum S { ____Placeholder_S } S ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_25__ {scalar_t__ (* close ) (TYPE_2__*) ;} ;
struct TYPE_24__ {size_t size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ DBT ;
typedef  TYPE_2__ DB ;

/* Variables and functions */
 int COMMAND ; 
#define  COMPARE 132 
 int DATA ; 
 scalar_t__ DB_BTREE ; 
 int DB_LOCK ; 
 scalar_t__ DB_RECNO ; 
#define  GET 131 
 int KEY ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
#define  PUT 130 
#define  REMOVE 129 
 int /*<<< orphan*/  R_CURSOR ; 
#define  SEQ 128 
 scalar_t__ STDOUT_FILENO ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 TYPE_2__* XXdbp ; 
 int XXlineno ; 
 int /*<<< orphan*/  __bt_stat (TYPE_2__*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  chkcmd (int) ; 
 int /*<<< orphan*/  chkdata (int) ; 
 int /*<<< orphan*/  chkkey (int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  compare (TYPE_1__*,TYPE_1__*) ; 
 TYPE_2__* dbopen (char*,int,int,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ dbtype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,int,...) ; 
 char* fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  getdata (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/ * infop ; 
 scalar_t__ isspace (unsigned char) ; 
 int lineno ; 
 scalar_t__ ofd ; 
 scalar_t__ open (char*,int,int) ; 
 int /*<<< orphan*/  put (TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rem (TYPE_2__*,TYPE_1__*) ; 
 void* rfile (char*,size_t*) ; 
 int /*<<< orphan*/  seq (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  setflags (char*) ; 
 int /*<<< orphan*/ * setinfo (scalar_t__,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  synk (TYPE_2__*) ; 
 scalar_t__ type ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  unlinkpg (TYPE_2__*) ; 
 int /*<<< orphan*/  usage () ; 
 int write (scalar_t__,char*,int) ; 
 void* xcopy (char*,size_t) ; 

int
main(int argc, char *argv[])
{
	extern int optind;
	extern char *optarg;
	enum S command = COMMAND, state;
	DB *dbp;
	DBT data, key, keydata;
	size_t len;
	int ch, oflags, sflag;
	char *fname, *infoarg, *p, *t, buf[8 * 1024];
	bool unlink_dbfile;

	infoarg = NULL;
	fname = NULL;
	unlink_dbfile = false;
	oflags = O_CREAT | O_RDWR;
	sflag = 0;
	while ((ch = getopt(argc, argv, "f:i:lo:s")) != -1)
		switch (ch) {
		case 'f':
			fname = optarg;
			break;
		case 'i':
			infoarg = optarg;
			break;
		case 'l':
			oflags |= DB_LOCK;
			break;
		case 'o':
			if ((ofd = open(optarg,
			    O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
				err(1, "Cannot create `%s'", optarg);
			break;
		case 's':
			sflag = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc != 2)
		usage();

	/* Set the type. */
	type = dbtype(*argv++);

	/* Open the descriptor file. */
        if (strcmp(*argv, "-") && freopen(*argv, "r", stdin) == NULL)
	    err(1, "Cannot reopen `%s'", *argv);

	/* Set up the db structure as necessary. */
	if (infoarg == NULL)
		infop = NULL;
	else
		for (p = strtok(infoarg, ",\t "); p != NULL;
		    p = strtok(0, ",\t "))
			if (*p != '\0')
				infop = setinfo(type, p);

	/*
	 * Open the DB.  Delete any preexisting copy, you almost never
	 * want it around, and it often screws up tests.
	 */
	if (fname == NULL) {
		const char *q = getenv("TMPDIR");
		if (q == NULL)
			q = "/var/tmp";
		(void)snprintf(buf, sizeof(buf), "%s/__dbtest", q);
		fname = buf;
		(void)unlink(buf);
		unlink_dbfile = true;
	} else  if (!sflag)
		(void)unlink(fname);

	if ((dbp = dbopen(fname,
	    oflags, S_IRUSR | S_IWUSR, type, infop)) == NULL)
		err(1, "Cannot dbopen `%s'", fname);
	XXdbp = dbp;
	if (unlink_dbfile)
		(void)unlink(fname);

	state = COMMAND;
	for (lineno = 1;
	    (p = fgets(buf, sizeof(buf), stdin)) != NULL; ++lineno) {
		/* Delete the newline, displaying the key/data is easier. */
		if (ofd == STDOUT_FILENO && (t = strchr(p, '\n')) != NULL)
			*t = '\0';
		if ((len = strlen(buf)) == 0 || isspace((unsigned char)*p) ||
		    *p == '#')
			continue;

		/* Convenient gdb break point. */
		if (XXlineno == lineno)
			XXlineno = 1;
		switch (*p) {
		case 'c':			/* compare */
			chkcmd(state);
			state = KEY;
			command = COMPARE;
			break;
		case 'e':			/* echo */
			chkcmd(state);
			/* Don't display the newline, if CR at EOL. */
			if (p[len - 2] == '\r')
				--len;
			if (write(ofd, p + 1, len - 1) != (ssize_t)len - 1 ||
			    write(ofd, "\n", 1) != 1)
				err(1, "write failed");
			break;
		case 'g':			/* get */
			chkcmd(state);
			state = KEY;
			command = GET;
			break;
		case 'p':			/* put */
			chkcmd(state);
			state = KEY;
			command = PUT;
			break;
		case 'r':			/* remove */
			chkcmd(state);
                        if (flags == R_CURSOR) {
				rem(dbp, &key);
				state = COMMAND;
                        } else {
				state = KEY;
				command = REMOVE;
			}
			break;
		case 'S':			/* sync */
			chkcmd(state);
			synk(dbp);
			state = COMMAND;
			break;
		case 's':			/* seq */
			chkcmd(state);
			if (flags == R_CURSOR) {
				state = KEY;
				command = SEQ;
			} else
				seq(dbp, &key);
			break;
		case 'f':
			flags = setflags(p + 1);
			break;
		case 'D':			/* data file */
			chkdata(state);
			data.data = rfile(p + 1, &data.size);
			goto ldata;
		case 'd':			/* data */
			chkdata(state);
			data.data = xcopy(p + 1, len - 1);
			data.size = len - 1;
ldata:			switch (command) {
			case COMPARE:
				compare(&keydata, &data);
				break;
			case PUT:
				put(dbp, &key, &data);
				break;
			default:
				errx(1, "line %zu: command doesn't take data",
				    lineno);
			}
			if (type != DB_RECNO)
				free(key.data);
			free(data.data);
			state = COMMAND;
			break;
		case 'K':			/* key file */
			chkkey(state);
			if (type == DB_RECNO)
				errx(1, "line %zu: 'K' not available for recno",
				    lineno);
			key.data = rfile(p + 1, &key.size);
			goto lkey;
		case 'k':			/* key */
			chkkey(state);
			if (type == DB_RECNO) {
				static recno_t recno;
				recno = atoi(p + 1);
				key.data = &recno;
				key.size = sizeof(recno);
			} else {
				key.data = xcopy(p + 1, len - 1);
				key.size = len - 1;
			}
lkey:			switch (command) {
			case COMPARE:
				getdata(dbp, &key, &keydata);
				state = DATA;
				break;
			case GET:
				get(dbp, &key);
				if (type != DB_RECNO)
					free(key.data);
				state = COMMAND;
				break;
			case PUT:
				state = DATA;
				break;
			case REMOVE:
				rem(dbp, &key);
				if ((type != DB_RECNO) && (flags != R_CURSOR))
					free(key.data);
				state = COMMAND;
				break;
			case SEQ:
				seq(dbp, &key);
				if ((type != DB_RECNO) && (flags != R_CURSOR))
					free(key.data);
				state = COMMAND;
				break;
			default:
				errx(1, "line %zu: command doesn't take a key",
				    lineno);
			}
			break;
		case 'o':
			dump(dbp, p[1] == 'r', 0);
			break;
#ifdef	__NetBSD__
		case 'O':
			dump(dbp, p[1] == 'r', 1);
			break;
		case 'u':
			unlinkpg(dbp);
			break;
#endif
		default:
			errx(1, "line %zu: %s: unknown command character",
			    lineno, p);
		}
	}
#ifdef STATISTICS
	/*
	 * -l must be used (DB_LOCK must be set) for this to be
	 * used, otherwise a page will be locked and it will fail.
	 */
	if (type == DB_BTREE && oflags & DB_LOCK)
		__bt_stat(dbp);
#endif
	if ((*dbp->close)(dbp))
		err(1, "db->close failed");
	(void)close(ofd);
	return 0;
}