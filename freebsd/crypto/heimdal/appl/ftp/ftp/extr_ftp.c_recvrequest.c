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
struct timezone {int dummy; } ;
struct timeval {int dummy; } ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/ * sighand ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CONTINUE ; 
 scalar_t__ EACCES ; 
 scalar_t__ ENOENT ; 
 int EOF ; 
 scalar_t__ EPIPE ; 
 long HASHBYTES ; 
 scalar_t__ PRELIM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/ * SIG_IGN ; 
#define  TYPE_A 130 
#define  TYPE_I 129 
#define  TYPE_L 128 
 int /*<<< orphan*/  abort_remote (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * abortrecv ; 
 scalar_t__ access (char*,int) ; 
 char* alloc_buffer (char*,size_t*,struct stat*) ; 
 int /*<<< orphan*/  changetype (int,int /*<<< orphan*/ ) ; 
 scalar_t__ chmod (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int code ; 
 scalar_t__ command (char*,...) ; 
 scalar_t__ cpend ; 
 int /*<<< orphan*/  crflag ; 
 int curtype ; 
 int data ; 
 int /*<<< orphan*/ * dataconn (char*) ; 
 scalar_t__ errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  getreply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,struct timezone*) ; 
 char* gunique (char*) ; 
 int /*<<< orphan*/  hash ; 
 scalar_t__ initconn () ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  proxtrans (char*,char*,char*) ; 
 scalar_t__ proxy ; 
 int /*<<< orphan*/  ptransfer (char*,long,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  putc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  recvabort ; 
 int restart_point ; 
 scalar_t__ runique ; 
 int sec_getc (int /*<<< orphan*/ *) ; 
 int sec_read (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  set_buffer_size (int /*<<< orphan*/ ,int) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * signal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ *) ; 
 int stub4 (int /*<<< orphan*/ *) ; 
 int type ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void
recvrequest (char *cmd, char *local, char *remote,
	     char *lmode, int printnames, int local_given)
{
    FILE *fout = NULL, *din = NULL;
    int (*closefunc) (FILE *);
    sighand oldintr, oldintp;
    int c, d, is_retr, tcrflag, bare_lfs = 0;
    static size_t bufsize;
    static char *buf;
    long bytes = 0, hashbytes = HASHBYTES;
    struct timeval start, stop;
    struct stat st;

    is_retr = strcmp (cmd, "RETR") == 0;
    if (is_retr && verbose && printnames) {
	if (strcmp (local, "-") != 0)
	    printf ("local: %s ", local);
	if (remote)
	    printf ("remote: %s\n", remote);
    }
    if (proxy && is_retr) {
	proxtrans (cmd, local, remote);
	return;
    }
    closefunc = NULL;
    oldintr = NULL;
    oldintp = NULL;
    tcrflag = !crflag && is_retr;
    if (setjmp (recvabort)) {
	while (cpend) {
	    getreply (0);
	}
	if (data >= 0) {
	    close (data);
	    data = -1;
	}
	if (oldintr)
	    signal (SIGINT, oldintr);
	code = -1;
	return;
    }
    oldintr = signal (SIGINT, abortrecv);
    if (!local_given || (strcmp(local, "-") && *local != '|')) {
	if (access (local, 2) < 0) {
	    char *dir = strrchr (local, '/');

	    if (errno != ENOENT && errno != EACCES) {
		warn ("local: %s", local);
		signal (SIGINT, oldintr);
		code = -1;
		return;
	    }
	    if (dir != NULL)
		*dir = 0;
	    d = access (dir ? local : ".", 2);
	    if (dir != NULL)
		*dir = '/';
	    if (d < 0) {
		warn ("local: %s", local);
		signal (SIGINT, oldintr);
		code = -1;
		return;
	    }
	    if (!runique && errno == EACCES &&
		chmod (local, 0600) < 0) {
		warn ("local: %s", local);
		signal (SIGINT, oldintr);
		signal (SIGINT, oldintr);
		code = -1;
		return;
	    }
	    if (runique && errno == EACCES &&
		(local = gunique (local)) == NULL) {
		signal (SIGINT, oldintr);
		code = -1;
		return;
	    }
	} else if (runique && (local = gunique (local)) == NULL) {
	    signal(SIGINT, oldintr);
	    code = -1;
	    return;
	}
    }
    if (!is_retr) {
	if (curtype != TYPE_A)
	    changetype (TYPE_A, 0);
    } else if (curtype != type)
	changetype (type, 0);
    if (initconn ()) {
	signal (SIGINT, oldintr);
	code = -1;
	return;
    }
    if (setjmp (recvabort))
	goto abort;
    if (is_retr && restart_point &&
	command ("REST %ld", (long) restart_point) != CONTINUE)
	return;
    if (remote) {
	if (command ("%s %s", cmd, remote) != PRELIM) {
	    signal (SIGINT, oldintr);
	    return;
	}
    } else {
	if (command ("%s", cmd) != PRELIM) {
	    signal (SIGINT, oldintr);
	    return;
	}
    }
    din = dataconn ("r");
    if (din == NULL)
	goto abort;
    set_buffer_size (fileno (din), 1);
    if (local_given && strcmp (local, "-") == 0)
	fout = stdout;
    else if (local_given && *local == '|') {
	oldintp = signal (SIGPIPE, SIG_IGN);
	fout = popen (local + 1, "w");
	if (fout == NULL) {
	    warn ("%s", local + 1);
	    goto abort;
	}
	closefunc = pclose;
    } else {
	fout = fopen (local, lmode);
	if (fout == NULL) {
	    warn ("local: %s", local);
	    goto abort;
	}
	closefunc = fclose;
    }
    buf = alloc_buffer (buf, &bufsize,
			fstat (fileno (fout), &st) >= 0 ? &st : NULL);
    if (buf == NULL)
	goto abort;

    gettimeofday (&start, (struct timezone *) 0);
    switch (curtype) {

    case TYPE_I:
    case TYPE_L:
	if (restart_point &&
	    lseek (fileno (fout), restart_point, SEEK_SET) < 0) {
	    warn ("local: %s", local);
	    if (closefunc != NULL)
		(*closefunc) (fout);
	    return;
	}
	errno = d = 0;
	while ((c = sec_read (fileno (din), buf, bufsize)) > 0) {
	    if ((d = write (fileno (fout), buf, c)) != c)
		break;
	    bytes += c;
	    if (hash) {
		while (bytes >= hashbytes) {
		    putchar ('#');
		    hashbytes += HASHBYTES;
		}
		fflush (stdout);
	    }
	}
	if (hash && bytes > 0) {
	    if (bytes < HASHBYTES)
		putchar ('#');
	    putchar ('\n');
	    fflush (stdout);
	}
	if (c < 0) {
	    if (errno != EPIPE)
		warn ("netin");
	    bytes = -1;
	}
	if (d < c) {
	    if (d < 0)
		warn ("local: %s", local);
	    else
		warnx ("%s: short write", local);
	}
	break;

    case TYPE_A:
	if (restart_point) {
	    int i, n, ch;

	    if (fseek (fout, 0L, SEEK_SET) < 0)
		goto done;
	    n = restart_point;
	    for (i = 0; i++ < n;) {
		if ((ch = sec_getc (fout)) == EOF)
		    goto done;
		if (ch == '\n')
		    i++;
	    }
	    if (fseek (fout, 0L, SEEK_CUR) < 0) {
	done:
		warn ("local: %s", local);
		if (closefunc != NULL)
		    (*closefunc) (fout);
		return;
	    }
	}
	while ((c = sec_getc(din)) != EOF) {
	    if (c == '\n')
		bare_lfs++;
	    while (c == '\r') {
		while (hash && (bytes >= hashbytes)) {
		    putchar ('#');
		    fflush (stdout);
		    hashbytes += HASHBYTES;
		}
		bytes++;
		if ((c = sec_getc (din)) != '\n' || tcrflag) {
		    if (ferror (fout))
			goto break2;
		    putc ('\r', fout);
		    if (c == '\0') {
			bytes++;
			goto contin2;
		    }
		    if (c == EOF)
			goto contin2;
		}
	    }
	    putc (c, fout);
	    bytes++;
    contin2:;
	}
break2:
	if (bare_lfs) {
	    printf ("WARNING! %d bare linefeeds received in ASCII mode\n",
		    bare_lfs);
	    printf ("File may not have transferred correctly.\n");
	}
	if (hash) {
	    if (bytes < hashbytes)
		putchar ('#');
	    putchar ('\n');
	    fflush (stdout);
	}
	if (ferror (din)) {
	    if (errno != EPIPE)
		warn ("netin");
	    bytes = -1;
	}
	if (ferror (fout))
	    warn ("local: %s", local);
	break;
    }
    if (closefunc != NULL)
	(*closefunc) (fout);
    signal (SIGINT, oldintr);
    if (oldintp)
	signal (SIGPIPE, oldintp);
    fclose (din);
    gettimeofday (&stop, (struct timezone *) 0);
    getreply (0);
    if (bytes > 0 && is_retr)
	ptransfer ("received", bytes, &start, &stop);
    return;
abort:

    /* abort using RFC959 recommended IP,SYNC sequence  */

    if (oldintp)
	signal (SIGPIPE, oldintr);
    signal (SIGINT, SIG_IGN);
    if (!cpend) {
	code = -1;
	signal (SIGINT, oldintr);
	return;
    }
    abort_remote(din);
    code = -1;
    if (data >= 0) {
	close (data);
	data = -1;
    }
    if (closefunc != NULL && fout != NULL)
	(*closefunc) (fout);
    if (din)
	fclose (din);
    gettimeofday (&stop, (struct timezone *) 0);
    if (bytes > 0)
	ptransfer ("received", bytes, &start, &stop);
    signal (SIGINT, oldintr);
}