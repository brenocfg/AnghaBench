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
typedef  scalar_t__ u_char ;

/* Variables and functions */
 int DWIDTH ; 
 scalar_t__ MAXMSG ; 
 int NBYTES ; 
 scalar_t__ NCHARS ; 
 int* asc_ptr ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int* data_table ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fgets (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int i ; 
 size_t j ; 
 char* line ; 
 int linen ; 
 char* malloc (size_t) ; 
 int max ; 
 char* message ; 
 int nchars ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int pc ; 
 int* print ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 int term ; 
 int trace ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char) ; 
 int width ; 
 int x ; 
 int y ; 

int
main(int argc, char *argv[])
{
	int ch;

	while ((ch = getopt(argc, argv, "w:td")) != -1)
		switch (ch) {
		case 'd':
			debug = 1;
			break;
		case 't':
			trace = 1;
			break;
		case 'w':
			width = atoi(optarg);
			if (width <= 0 || width > DWIDTH)
				errx(1, "illegal argument for -w option");
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	for (i = 0; i < width; i++) {
		j = i * DWIDTH / width;
		print[j] = 1;
	}

	/* Have now read in the data. Next get the message to be printed. */
	if (*argv) {
		for(i=0, j=0; i < argc; i++)
			j += strlen(argv[i]) + 1;
		if ((message = malloc((size_t)j)) == NULL) 
			err(1, "malloc");
		strlcpy(message, *argv, j);
		while (*++argv) {
			strlcat(message, " ", j);
			strlcat(message, *argv, j);
		}
		nchars = strlen(message);
	} else {
		if ((message = malloc((size_t)MAXMSG)) == NULL)
			err(1, "malloc");
		fprintf(stderr,"Message: ");
		if (fgets(message, MAXMSG, stdin) == NULL) {
			nchars = 0;
			message[0] = '\0';
		} else {
			nchars = strlen(message);

			/* Get rid of newline. */
			if (message[nchars - 1] == '\n')
				message[--nchars] = '\0';
		}
	}

	/* some debugging print statements */
	if (debug) {
		printf("const int asc_ptr[NCHARS] = {\n");
		for (i = 0; i < 128; i++) {
			printf("%4d,   ",asc_ptr[i]);
			if ((i+1) % 8 == 0)
				printf("\n");
		}
		printf("};\nconst unsigned char data_table[NBYTES] = {\n");
		printf("/*          ");
		for (i = 0; i < 10; i++) printf(" %3d  ",i);
		printf("*/\n");
		for (i = 0; i < NBYTES; i += 10) {
			printf("/* %4d */  ",i);
			for (j = i; j < i+10; j++) {
				x = data_table[j] & 0377;
				printf(" %3d, ",x);
			}
			putchar('\n');
		}
		printf("};\n");
	}

	/* check message to make sure it's legal */
	j = 0;
	for (i = 0; i < nchars; i++)
		if ((u_char) message[i] >= NCHARS ||
		    asc_ptr[(u_char) message[i]] == 0) {
			warnx("the character '%c' is not in my character set",
				message[i]);
			j++;
		}
	if (j)
		exit(1);

	if (trace)
		printf("Message '%s' is OK\n",message);
	/* Now have message. Print it one character at a time.  */

	for (i = 0; i < nchars; i++) {
		if (trace)
			printf("Char #%d: %c\n", i, message[i]);
		for (j = 0; j < DWIDTH; j++) line[j] = ' ';
		pc = asc_ptr[(u_char) message[i]];
		term = 0;
		max = 0;
		linen = 0;
		while (!term) {
			if (pc < 0 || pc > NBYTES) {
				printf("bad pc: %d\n",pc);
				exit(1);
			}
			x = data_table[pc] & 0377;
			if (trace)
				printf("pc=%d, term=%d, max=%d, linen=%d, x=%d\n",pc,term,max,linen,x);
			if (x >= 128) {
				if (x>192) term++;
				x = x & 63;
				while (x--) {
					if (print[linen++]) {
						for (j=0; j <= max; j++)
							if (print[j])
								putchar(line[j]);
						putchar('\n');
					}
				}
				for (j = 0; j < DWIDTH; j++) line[j] = ' ';
				pc++;
			}
			else {
				y = data_table[pc+1];
				/* compensate for narrow teminals */
#ifdef notdef
				x = (x*width + (DWIDTH/2)) / DWIDTH;
				y = (y*width + (DWIDTH/2)) / DWIDTH;
#endif
				max = x+y;
				while (x < max) line[x++] = '#';
				pc += 2;
				if (trace)
					printf("x=%d, y=%d, max=%d\n",x,y,max);
			}
		}
	}

	free(message);
	exit(0);
}