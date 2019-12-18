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
 int /*<<< orphan*/  EncryptVerbose (int) ; 
 int /*<<< orphan*/  Exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetNetTrace (char*) ; 
 int /*<<< orphan*/  TerminalSaveState () ; 
 char _POSIX_VDISABLE ; 
 int /*<<< orphan*/  auth_disable_name (char*) ; 
 int autologin ; 
 int binary ; 
 int /*<<< orphan*/  command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int debug ; 
 int /*<<< orphan*/  decrypt_auto (int) ; 
 int eight ; 
 int /*<<< orphan*/  encrypt_auto (int) ; 
 int /*<<< orphan*/  env_define (unsigned char*,unsigned char*) ; 
 char escape ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int forward_option ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  krb5_init () ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int parsetos (char*,char*) ; 
 int /*<<< orphan*/  print_version (int /*<<< orphan*/ *) ; 
 char* prompt ; 
 char rlogin ; 
 int /*<<< orphan*/  set_escape_char (char*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setprogname (char*) ; 
 int skiprc ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strrchr (char*,char) ; 
 int tn (int,char**) ; 
 int /*<<< orphan*/  tninit () ; 
 int /*<<< orphan*/  toplevel ; 
 int /*<<< orphan*/  usage (int) ; 
 int wantencryption ; 

int
main(int argc, char **argv)
{
	int ch;
	char *user;

	setprogname(argv[0]);

#ifdef KRB5
	krb5_init();
#endif

	tninit();		/* Clear out things */

	TerminalSaveState();

	if ((prompt = strrchr(argv[0], '/')))
		++prompt;
	else
		prompt = argv[0];

	user = NULL;

	rlogin = (strncmp(prompt, "rlog", 4) == 0) ? '~' : _POSIX_VDISABLE;

	/*
	 * if AUTHENTICATION and ENCRYPTION is set autologin will be
	 * se to true after the getopt switch; unless the -K option is
	 * passed
	 */
	autologin = -1;

	if (argc == 2 && strcmp(argv[1], "--version") == 0) {
	    print_version(NULL);
	    exit(0);
	}
	if (argc == 2 && strcmp(argv[1], "--help") == 0)
	    usage(0);


	while((ch = getopt(argc, argv,
			   "78DEKLS:X:abcde:fFk:l:n:rxG")) != -1) {
		switch(ch) {
		case '8':
			eight = 3;	/* binary output and input */
			break;
		case '7':
			eight = 0;
			break;
		case 'b':
		    binary = 3;
		    break;
		case 'D': {
		    /* sometimes we don't want a mangled display */
		    char *p;
		    if((p = getenv("DISPLAY")))
			env_define((unsigned char*)"DISPLAY", (unsigned char*)p);
		    break;
		}
		case 'E':
			rlogin = escape = _POSIX_VDISABLE;
			break;
		case 'K':
#ifdef	AUTHENTICATION
			autologin = 0;
#endif
			break;
		case 'L':
			eight |= 2;	/* binary output only */
			break;
		case 'S':
		    {
#ifdef	HAVE_PARSETOS
			extern int tos;

			if ((tos = parsetos(optarg, "tcp")) < 0)
				fprintf(stderr, "%s%s%s%s\n",
					prompt, ": Bad TOS argument '",
					optarg,
					"; will try to use default TOS");
#else
			fprintf(stderr,
			   "%s: Warning: -S ignored, no parsetos() support.\n",
								prompt);
#endif
		    }
			break;
		case 'X':
#ifdef	AUTHENTICATION
			auth_disable_name(optarg);
#endif
			break;
		case 'a':
			autologin = 1;
			break;
		case 'c':
			skiprc = 1;
			break;
		case 'd':
			debug = 1;
			break;
		case 'e':
			set_escape_char(optarg);
			break;
		case 'f':
		case 'F':
		case 'G':
#if defined(AUTHENTICATION) && defined(KRB5) && defined(FORWARD)
			if (forward_option) {
			    fprintf(stderr,
				    "%s: Only one of -f, -F and -G allowed.\n",
				    prompt);
			    usage(1);
			}
			forward_option = ch;
#else
			fprintf(stderr,
			 "%s: Warning: -%c ignored, no Kerberos V5 support.\n",
				prompt, ch);
#endif
			break;
		case 'k':
		    fprintf(stderr,
			    "%s: Warning: -k ignored, no Kerberos V4 support.\n",
			    prompt);
		    break;
		case 'l':
		  if(autologin == 0){
		    fprintf(stderr, "%s: Warning: -K ignored\n", prompt);
		    autologin = -1;
		  }
			user = optarg;
			break;
		case 'n':
				SetNetTrace(optarg);
			break;
		case 'r':
			rlogin = '~';
			break;
		case 'x':
#ifdef	ENCRYPTION
			encrypt_auto(1);
			decrypt_auto(1);
			wantencryption = 1;
			EncryptVerbose(1);
#else
			fprintf(stderr,
			    "%s: Warning: -x ignored, no ENCRYPT support.\n",
								prompt);
#endif
			break;

		case '?':
		default:
			usage(1);
			/* NOTREACHED */
		}
	}

	if (autologin == -1) {		/* esc@magic.fi; force  */
#if defined(AUTHENTICATION)
		autologin = 1;
#endif
#if defined(ENCRYPTION)
		encrypt_auto(1);
		decrypt_auto(1);
		wantencryption = -1;
#endif
	}

	if (autologin == -1)
		autologin = (rlogin == _POSIX_VDISABLE) ? 0 : 1;

	argc -= optind;
	argv += optind;

	if (argc) {
		char *args[7], **argp = args;

		if (argc > 2)
			usage(1);
		*argp++ = prompt;
		if (user) {
			*argp++ = "-l";
			*argp++ = user;
		}
		*argp++ = argv[0];		/* host */
		if (argc > 1)
			*argp++ = argv[1];	/* port */
		*argp = 0;

		if (setjmp(toplevel) != 0)
			Exit(0);
		if (tn(argp - args, args) == 1)
			return (0);
		else
			return (1);
	}
	setjmp(toplevel);
	for (;;) {
			command(1, 0, 0);
	}
}