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
typedef  int /*<<< orphan*/  wint_t ;
typedef  scalar_t__ wchar_t ;
typedef  scalar_t__ uintmax_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BINARY_BINARY_FILES ; 
#define  BINARY_FILES_OPTION 136 
 int BZflag ; 
#define  COLOR_OPTION 135 
 int /*<<< orphan*/  DOS_BINARY ; 
#define  EXCLUDE_FROM_OPTION 134 
#define  EXCLUDE_OPTION 133 
#define  INCLUDE_OPTION 132 
#define  LABEL_OPTION 131 
 int /*<<< orphan*/  LC_ALL ; 
#define  LINE_BUFFERED_OPTION 130 
 int /*<<< orphan*/  LOCALEDIR ; 
#define  LONGINT_OK 129 
#define  LONGINT_OVERFLOW 128 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  PACKAGE ; 
 int /*<<< orphan*/  READ_DEVICES ; 
 int /*<<< orphan*/  READ_DIRECTORIES ; 
 int /*<<< orphan*/  RECURSE_DIRECTORIES ; 
 int /*<<< orphan*/  SET_BINARY (int) ; 
 int /*<<< orphan*/  SKIP_DEVICES ; 
 int /*<<< orphan*/  SKIP_DIRECTORIES ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  TEXT_BINARY_FILES ; 
 scalar_t__ TYPE_MAXIMUM (int /*<<< orphan*/ ) ; 
 char* VERSION ; 
 int /*<<< orphan*/  WITHOUT_MATCH_BINARY_FILES ; 
 int Zflag ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  add_exclude (scalar_t__,char*) ; 
 int /*<<< orphan*/  add_exclude_file (int /*<<< orphan*/  (*) (scalar_t__,char*),scalar_t__,char*,char) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binary_files ; 
 int /*<<< orphan*/  bindtextdomain (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_stdout ; 
 int /*<<< orphan*/  close_stdout_set_status (int /*<<< orphan*/ ) ; 
 int color_option ; 
 int /*<<< orphan*/  compile (char*,size_t) ; 
 int /*<<< orphan*/  context_length_arg (char*,int*) ; 
 int count_matches ; 
 int /*<<< orphan*/  devices ; 
 int /*<<< orphan*/  directories ; 
 int done_on_match ; 
 int dos_report_unix_offset ; 
 int /*<<< orphan*/  dos_use_file_type ; 
 char eolbyte ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errseen ; 
 scalar_t__ excluded_filename (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ excluded_patterns ; 
 int /*<<< orphan*/  exit (int) ; 
 int exit_on_match ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename_mask ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_nondigit_option (int,char**,int*) ; 
 char* getenv (char*) ; 
 char* grep_color ; 
 int grepfile (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ included_patterns ; 
 int /*<<< orphan*/  initialize_main (int*,char***) ; 
 int /*<<< orphan*/  install_matcher (char*) ; 
 scalar_t__ isatty (int) ; 
 int /*<<< orphan*/  isdir (char*) ; 
 scalar_t__ iswupper (int /*<<< orphan*/ ) ; 
 char* label ; 
 int line_buffered ; 
 int list_files ; 
 int match_icase ; 
 int match_lines ; 
 int match_words ; 
 char* matcher ; 
 scalar_t__ max_count ; 
 size_t mbrtowc (scalar_t__*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ new_exclude () ; 
 int no_filenames ; 
 int /*<<< orphan*/  off_t ; 
 int only_matching ; 
 int out_after ; 
 int out_before ; 
 int out_byte ; 
 int out_file ; 
 int out_invert ; 
 int out_line ; 
 int out_quiet ; 
 int /*<<< orphan*/  prepend_default_options (char*,int*,char***) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* program_name ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setmatcher (char*) ; 
 int show_help ; 
 int show_version ; 
 int /*<<< orphan*/  stats_base ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 void* strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  stub1 (char*,size_t) ; 
 int suppress_errors ; 
 int /*<<< orphan*/  textdomain (int /*<<< orphan*/ ) ; 
 scalar_t__ towlower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  wcrtomb (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 char* xrealloc (char*,size_t) ; 
 int /*<<< orphan*/  xstrtoumax (char*,int /*<<< orphan*/ ,int,scalar_t__*,char*) ; 

int
main (int argc, char **argv)
{
  char *keys;
  size_t cc, keycc, oldcc, keyalloc;
  int with_filenames;
  int opt, status;
  int default_context;
  FILE *fp;
  extern char *optarg;
  extern int optind;

  initialize_main (&argc, &argv);
  program_name = argv[0];
  if (program_name && strrchr (program_name, '/'))
    program_name = strrchr (program_name, '/') + 1;

  if (program_name[0] == 'b' && program_name[1] == 'z') {
    BZflag = 1;
    program_name += 2;
  }
#if HAVE_LIBZ > 0
  else if (program_name[0] == 'z') {
    Zflag = 1;
    ++program_name;
  }
#endif

#if defined(__MSDOS__) || defined(_WIN32)
  /* DOS and MS-Windows use backslashes as directory separators, and usually
     have an .exe suffix.  They also have case-insensitive filesystems.  */
  if (program_name)
    {
      char *p = program_name;
      char *bslash = strrchr (argv[0], '\\');

      if (bslash && bslash >= program_name) /* for mixed forward/backslash case */
	program_name = bslash + 1;
      else if (program_name == argv[0]
	       && argv[0][0] && argv[0][1] == ':') /* "c:progname" */
	program_name = argv[0] + 2;

      /* Collapse the letter-case, so `strcmp' could be used hence.  */
      for ( ; *p; p++)
	if (*p >= 'A' && *p <= 'Z')
	  *p += 'a' - 'A';

      /* Remove the .exe extension, if any.  */
      if ((p = strrchr (program_name, '.')) && strcmp (p, ".exe") == 0)
	*p = '\0';
    }
#endif

  keys = NULL;
  keycc = 0;
  with_filenames = 0;
  eolbyte = '\n';
  filename_mask = ~0;

  max_count = TYPE_MAXIMUM (off_t);

  /* The value -1 means to use DEFAULT_CONTEXT. */
  out_after = out_before = -1;
  /* Default before/after context: chaged by -C/-NUM options */
  default_context = 0;
  /* Changed by -o option */
  only_matching = 0;

  /* Internationalization. */
#if defined(HAVE_SETLOCALE)
  setlocale (LC_ALL, "");
#endif
#if defined(ENABLE_NLS)
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
#endif

  atexit (close_stdout);

  prepend_default_options (getenv ("GREP_OPTIONS"), &argc, &argv);

  while ((opt = get_nondigit_option (argc, argv, &default_context)) != -1)
    switch (opt)
      {
      case 'A':
	context_length_arg (optarg, &out_after);
	break;

      case 'B':
	context_length_arg (optarg, &out_before);
	break;

      case 'C':
	/* Set output match context, but let any explicit leading or
	   trailing amount specified with -A or -B stand. */
	context_length_arg (optarg, &default_context);
	break;

      case 'D':
	if (strcmp (optarg, "read") == 0)
	  devices = READ_DEVICES;
	else if (strcmp (optarg, "skip") == 0)
	  devices = SKIP_DEVICES;
	else
	  error (2, 0, _("unknown devices method"));
	break;

      case 'E':
	setmatcher ("egrep");
	break;

      case 'F':
	setmatcher ("fgrep");
	break;

      case 'P':
	setmatcher ("perl");
	break;

      case 'G':
	setmatcher ("grep");
	break;

      case 'H':
	with_filenames = 1;
	break;

      case 'I':
	binary_files = WITHOUT_MATCH_BINARY_FILES;
	break;
      case 'J':
	if (Zflag)
	  {
	    printf (_("Cannot mix -Z and -J.\n"));
	    usage (2);
	  }
	BZflag = 1;
	break;

      case 'U':
#if defined(HAVE_DOS_FILE_CONTENTS)
	dos_use_file_type = DOS_BINARY;
#endif
	break;

      case 'u':
#if defined(HAVE_DOS_FILE_CONTENTS)
	dos_report_unix_offset = 1;
#endif
	break;

      case 'V':
	show_version = 1;
	break;

      case 'X':
	setmatcher (optarg);
	break;

      case 'a':
	binary_files = TEXT_BINARY_FILES;
	break;

      case 'b':
	out_byte = 1;
	break;

      case 'c':
	count_matches = 1;
	break;

      case 'd':
	if (strcmp (optarg, "read") == 0)
	  directories = READ_DIRECTORIES;
	else if (strcmp (optarg, "skip") == 0)
	  directories = SKIP_DIRECTORIES;
	else if (strcmp (optarg, "recurse") == 0)
	  directories = RECURSE_DIRECTORIES;
	else
	  error (2, 0, _("unknown directories method"));
	break;

      case 'e':
	cc = strlen (optarg);
	keys = xrealloc (keys, keycc + cc + 1);
	strcpy (&keys[keycc], optarg);
	keycc += cc;
	keys[keycc++] = '\n';
	break;

      case 'f':
	fp = strcmp (optarg, "-") != 0 ? fopen (optarg, "r") : stdin;
	if (!fp)
	  error (2, errno, "%s", optarg);
	for (keyalloc = 1; keyalloc <= keycc + 1; keyalloc *= 2)
	  ;
	keys = xrealloc (keys, keyalloc);
	oldcc = keycc;
	while (!feof (fp)
	       && (cc = fread (keys + keycc, 1, keyalloc - 1 - keycc, fp)) > 0)
	  {
	    keycc += cc;
	    if (keycc == keyalloc - 1)
	      keys = xrealloc (keys, keyalloc *= 2);
	  }
	if (fp != stdin)
	  fclose(fp);
	/* Append final newline if file ended in non-newline. */
	if (oldcc != keycc && keys[keycc - 1] != '\n')
	  keys[keycc++] = '\n';
	break;

      case 'h':
	no_filenames = 1;
	break;

      case 'i':
      case 'y':			/* For old-timers . . . */
	match_icase = 1;
	break;

      case 'L':
	/* Like -l, except list files that don't contain matches.
	   Inspired by the same option in Hume's gre. */
	list_files = -1;
	break;

      case 'l':
	list_files = 1;
	break;

      case 'm':
	{
	  uintmax_t value;
	  switch (xstrtoumax (optarg, 0, 10, &value, ""))
	    {
	    case LONGINT_OK:
	      max_count = value;
	      if (0 <= max_count && max_count == value)
		break;
	      /* Fall through.  */
	    case LONGINT_OVERFLOW:
	      max_count = TYPE_MAXIMUM (off_t);
	      break;

	    default:
	      error (2, 0, _("invalid max count"));
	    }
	}
	break;

      case 'n':
	out_line = 1;
	break;

      case 'o':
	only_matching = 1;
	break;

      case 'q':
	exit_on_match = 1;
	close_stdout_set_status(0);
	break;

      case 'R':
      case 'r':
	directories = RECURSE_DIRECTORIES;
	break;

      case 's':
	suppress_errors = 1;
	break;

      case 'v':
	out_invert = 1;
	break;

      case 'w':
	match_words = 1;
	break;

      case 'x':
	match_lines = 1;
	break;

      case 'Z':
#if HAVE_LIBZ > 0
	if (BZflag)
	  {
	    printf (_("Cannot mix -J and -Z.\n"));
	    usage (2);
	  }
	Zflag = 1;
#else
	filename_mask = 0;
#endif
	break;

      case 'z':
	eolbyte = '\0';
	break;

      case BINARY_FILES_OPTION:
	if (strcmp (optarg, "binary") == 0)
	  binary_files = BINARY_BINARY_FILES;
	else if (strcmp (optarg, "text") == 0)
	  binary_files = TEXT_BINARY_FILES;
	else if (strcmp (optarg, "without-match") == 0)
	  binary_files = WITHOUT_MATCH_BINARY_FILES;
	else
	  error (2, 0, _("unknown binary-files type"));
	break;

      case COLOR_OPTION:
        if(optarg) {
          if(!strcasecmp(optarg, "always") || !strcasecmp(optarg, "yes") ||
             !strcasecmp(optarg, "force"))
            color_option = 1;
          else if(!strcasecmp(optarg, "never") || !strcasecmp(optarg, "no") ||
                  !strcasecmp(optarg, "none"))
            color_option = 0;
          else if(!strcasecmp(optarg, "auto") || !strcasecmp(optarg, "tty") ||
                  !strcasecmp(optarg, "if-tty"))
            color_option = 2;
          else
            show_help = 1;
        } else
          color_option = 2;
        if(color_option == 2) {
          if(isatty(STDOUT_FILENO) && getenv("TERM") &&
	     strcmp(getenv("TERM"), "dumb"))
                  color_option = 1;
          else
            color_option = 0;
        }
	break;

      case EXCLUDE_OPTION:
	if (!excluded_patterns)
	  excluded_patterns = new_exclude ();
	add_exclude (excluded_patterns, optarg);
	break;

      case EXCLUDE_FROM_OPTION:
	if (!excluded_patterns)
	  excluded_patterns = new_exclude ();
        if (add_exclude_file (add_exclude, excluded_patterns, optarg, '\n')
	    != 0)
          {
            error (2, errno, "%s", optarg);
          }
        break;

      case INCLUDE_OPTION:
	if (!included_patterns)
	  included_patterns = new_exclude ();
	add_exclude (included_patterns, optarg);
	break;

      case LINE_BUFFERED_OPTION:
	line_buffered = 1;
	break;

      case LABEL_OPTION:
	label = optarg;
	break;

      case 0:
	/* long options */
	break;

      default:
	usage (2);
	break;

      }

  /* POSIX.2 says that -q overrides -l, which in turn overrides the
     other output options.  */
  if (exit_on_match)
    list_files = 0;
  if (exit_on_match | list_files)
    {
      count_matches = 0;
      done_on_match = 1;
    }
  out_quiet = count_matches | done_on_match;

  if (out_after < 0)
    out_after = default_context;
  if (out_before < 0)
    out_before = default_context;

  if (color_option)
    {
      char *userval = getenv ("GREP_COLOR");
      if (userval != NULL && *userval != '\0')
	grep_color = userval;
    }

  if (! matcher)
    matcher = program_name;

  if (show_version)
    {
      printf (_("%s (GNU grep) %s\n"), matcher, VERSION);
      printf ("\n");
      printf (_("\
Copyright 1988, 1992-1999, 2000, 2001 Free Software Foundation, Inc.\n"));
      printf (_("\
This is free software; see the source for copying conditions. There is NO\n\
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"));
      printf ("\n");
      exit (0);
    }

  if (show_help)
    usage (0);

  if (keys)
    {
      if (keycc == 0)
	{
	  /* No keys were specified (e.g. -f /dev/null).  Match nothing.  */
	  out_invert ^= 1;
	  match_lines = match_words = 0;
	}
      else
	/* Strip trailing newline. */
        --keycc;
    }
  else
    if (optind < argc)
      {
	keys = argv[optind++];
	keycc = strlen (keys);
      }
    else
      usage (2);

  if (!install_matcher (matcher) && !install_matcher ("default"))
    abort ();

#ifdef MBS_SUPPORT
  if (MB_CUR_MAX != 1 && match_icase)
    {
      wchar_t wc;
      mbstate_t cur_state, prev_state;
      int i, len = strlen(keys);

      memset(&cur_state, 0, sizeof(mbstate_t));
      for (i = 0; i <= len ;)
	{
	  size_t mbclen;
	  mbclen = mbrtowc(&wc, keys + i, len - i, &cur_state);
	  if (mbclen == (size_t) -1 || mbclen == (size_t) -2 || mbclen == 0)
	    {
	      /* An invalid sequence, or a truncated multibyte character.
		 We treat it as a singlebyte character.  */
	      mbclen = 1;
	    }
	  else
	    {
	      if (iswupper((wint_t)wc))
		{
		  wc = towlower((wint_t)wc);
		  wcrtomb(keys + i, wc, &cur_state);
		}
	    }
	  i += mbclen;
	}
    }
#endif /* MBS_SUPPORT */

  (*compile)(keys, keycc);

  if ((argc - optind > 1 && !no_filenames) || with_filenames)
    out_file = 1;

#ifdef SET_BINARY
  /* Output is set to binary mode because we shouldn't convert
     NL to CR-LF pairs, especially when grepping binary files.  */
  if (!isatty (1))
    SET_BINARY (1);
#endif

  if (max_count == 0)
    exit (1);

  if (optind < argc)
    {
	status = 1;
	do
	{
	  char *file = argv[optind];
	  if ((included_patterns || excluded_patterns)
	      && !isdir (file))
	    {
	      if (included_patterns &&
		  ! excluded_filename (included_patterns, file, 0))
		continue;
	      if (excluded_patterns &&
		  excluded_filename (excluded_patterns, file, 0))
		continue;
	    }
	  status &= grepfile (strcmp (file, "-") == 0 ? (char *) NULL : file,
			      &stats_base);
	}
	while ( ++optind < argc);
    }
  else
    status = grepfile ((char *) NULL, &stats_base);

  /* We register via atexit() to test stdout.  */
  exit (errseen ? 2 : status);
}