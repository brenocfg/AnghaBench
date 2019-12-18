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
typedef  int /*<<< orphan*/  sig_t ;
typedef  int intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  MTWEOF ; 
 int NOCOUNT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIG_IGN ; 
 char* _PATH_DEFTAPE ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int filen ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* getspace (int) ; 
 int guesslen ; 
 int /*<<< orphan*/  intr ; 
 scalar_t__ lastrec ; 
 int maxblk ; 
 int /*<<< orphan*/  msg ; 
 int open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int read (int,char*,int) ; 
 scalar_t__ record ; 
 int /*<<< orphan*/  rewind_tape (int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ size ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ tsize ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verify (int,int,char*) ; 
 int /*<<< orphan*/  warn (char*,int,int) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 int write (int,char*,int) ; 
 int /*<<< orphan*/  writeop (int,int /*<<< orphan*/ ) ; 

int
main(int argc, char *argv[])
{
	int lastnread, nread, nw, inp, outp;
	enum {READ, VERIFY, COPY, COPYVERIFY} op = READ;
	sig_t oldsig;
	int ch, needeof;
	char *buff;
	const char *inf;

	msg = stdout;
	guesslen = 1;
	outp = -1;
	while ((ch = getopt(argc, argv, "cs:vx")) != -1)
		switch((char)ch) {
		case 'c':
			op = COPYVERIFY;
			break;
		case 's':
			maxblk = atoi(optarg);
			if (maxblk <= 0) {
				warnx("illegal block size");
				usage();
			}
			guesslen = 0;
			break;
		case 'v':
			op = VERIFY;
			break;
		case 'x':
			msg = stderr;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	switch(argc) {
	case 0:
		if (op != READ)
			usage();
		inf = _PATH_DEFTAPE;
		break;
	case 1:
		if (op != READ)
			usage();
		inf = argv[0];
		break;
	case 2:
		if (op == READ)
			op = COPY;
		inf = argv[0];
		if ((outp = open(argv[1], op == VERIFY ? O_RDONLY :
		    op == COPY ? O_WRONLY : O_RDWR, DEFFILEMODE)) < 0)
			err(3, "%s", argv[1]);
		break;
	default:
		usage();
	}

	if ((inp = open(inf, O_RDONLY, 0)) < 0)
		err(1, "%s", inf);

	buff = getspace(maxblk);

	if (op == VERIFY) {
		verify(inp, outp, buff);
		exit(0);
	}

	if ((oldsig = signal(SIGINT, SIG_IGN)) != SIG_IGN)
		(void) signal(SIGINT, intr);

	needeof = 0;
	for (lastnread = NOCOUNT;;) {
		if ((nread = read(inp, buff, maxblk)) == -1) {
			while (errno == EINVAL && (maxblk -= 1024)) {
				nread = read(inp, buff, maxblk);
				if (nread >= 0)
					goto r1;
			}
			err(1, "read error, file %d, record %ju", filen, (intmax_t)record);
		} else if (nread != lastnread) {
			if (lastnread != 0 && lastnread != NOCOUNT) {
				if (lastrec == 0 && nread == 0)
					fprintf(msg, "%ju records\n", (intmax_t)record);
				else if (record - lastrec > 1)
					fprintf(msg, "records %ju to %ju\n",
					    (intmax_t)lastrec, (intmax_t)record);
				else
					fprintf(msg, "record %ju\n", (intmax_t)lastrec);
			}
			if (nread != 0)
				fprintf(msg, "file %d: block size %d: ",
				    filen, nread);
			(void) fflush(stdout);
			lastrec = record;
		}
r1:		guesslen = 0;
		if (nread > 0) {
			if (op == COPY || op == COPYVERIFY) {
				if (needeof) {
					writeop(outp, MTWEOF);
					needeof = 0;
				}
				nw = write(outp, buff, nread);
				if (nw != nread) {
					if (nw == -1) {
						warn("write error, file %d, record %ju", filen,
						    (intmax_t)record);
					} else {
						warnx("write error, file %d, record %ju", filen,
						    (intmax_t)record);
						warnx("write (%d) != read (%d)", nw, nread);
					}
					errx(5, "copy aborted");
				}
			}
			size += nread;
			record++;
		} else {
			if (lastnread <= 0 && lastnread != NOCOUNT) {
				fprintf(msg, "eot\n");
				break;
			}
			fprintf(msg,
			    "file %d: eof after %ju records: %ju bytes\n",
			    filen, (intmax_t)record, (intmax_t)size);
			needeof = 1;
			filen++;
			tsize += size;
			size = record = lastrec = 0;
			lastnread = 0;
		}
		lastnread = nread;
	}
	fprintf(msg, "total length: %ju bytes\n", (intmax_t)tsize);
	(void)signal(SIGINT, oldsig);
	if (op == COPY || op == COPYVERIFY) {
		writeop(outp, MTWEOF);
		writeop(outp, MTWEOF);
		if (op == COPYVERIFY) {
			rewind_tape(outp);
			rewind_tape(inp);
			verify(inp, outp, buff);
		}
	}
	exit(0);
}