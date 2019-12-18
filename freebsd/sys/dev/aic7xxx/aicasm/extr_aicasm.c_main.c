#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; } ;
typedef  TYPE_1__ scope_t ;
typedef  TYPE_2__* path_entry_t ;
struct TYPE_11__ {int quoted_includes_only; scalar_t__ type; int /*<<< orphan*/ * directory; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_CANTCREAT ; 
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 scalar_t__ SCOPE_ROOT ; 
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* SLIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOURCE_FILE ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 char* appname ; 
 int /*<<< orphan*/  back_patch () ; 
 int /*<<< orphan*/  cs_tailq ; 
 int /*<<< orphan*/  dump_scope (TYPE_2__*) ; 
 void* fopen (void*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  include_file (char*,int /*<<< orphan*/ ) ; 
 int includes_search_curdir ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/ * listfile ; 
 void* listfilename ; 
 int /*<<< orphan*/  malloc (int) ; 
 int mm_flex_debug ; 
 int mmdebug ; 
 int /*<<< orphan*/ * ofile ; 
 void* ofilename ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  output_code () ; 
 int /*<<< orphan*/  output_listing (char*) ; 
 int /*<<< orphan*/  patches ; 
 int /*<<< orphan*/  perror (void*) ; 
 int /*<<< orphan*/  process_scope (TYPE_2__*) ; 
 int /*<<< orphan*/ * regdiagfile ; 
 void* regdiagfilename ; 
 int /*<<< orphan*/ * regfile ; 
 void* regfilename ; 
 TYPE_1__* scope_alloc () ; 
 int /*<<< orphan*/  scope_stack ; 
 int /*<<< orphan*/  search_path ; 
 int /*<<< orphan*/  seq_program ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stock_include_file ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (void*,char*) ; 
 int /*<<< orphan*/ * strdup (void*) ; 
 int /*<<< orphan*/  symtable_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symtable_open () ; 
 int /*<<< orphan*/  usage () ; 
 int yy_flex_debug ; 
 int yydebug ; 
 int yyparse () ; 

int
main(int argc, char *argv[])
{
	int  ch;
	int  retval;
	char *inputfilename;
	scope_t *sentinal;

	STAILQ_INIT(&patches);
	SLIST_INIT(&search_path);
	STAILQ_INIT(&seq_program);
	TAILQ_INIT(&cs_tailq);
	SLIST_INIT(&scope_stack);

	/* Set Sentinal scope node */
	sentinal = scope_alloc();
	sentinal->type = SCOPE_ROOT;
	
	includes_search_curdir = 1;
	appname = *argv;
	regfile = NULL;
	listfile = NULL;
#if DEBUG
	yy_flex_debug = 0;
	mm_flex_debug = 0;
	yydebug = 0;
	mmdebug = 0;
#endif
	while ((ch = getopt(argc, argv, "d:i:l:n:o:p:r:I:X")) != -1) {
		switch(ch) {
		case 'd':
#if DEBUG
			if (strcmp(optarg, "s") == 0) {
				yy_flex_debug = 1;
				mm_flex_debug = 1;
			} else if (strcmp(optarg, "p") == 0) {
				yydebug = 1;
				mmdebug = 1;
			} else {
				fprintf(stderr, "%s: -d Requires either an "
					"'s' or 'p' argument\n", appname);
				usage();
			}
#else
			stop("-d: Assembler not built with debugging "
			     "information", EX_SOFTWARE);
#endif
			break;
		case 'i':
			stock_include_file = optarg;
			break;
		case 'l':
			/* Create a program listing */
			if ((listfile = fopen(optarg, "w")) == NULL) {
				perror(optarg);
				stop(NULL, EX_CANTCREAT);
			}
			listfilename = optarg;
			break;
		case 'n':
			/* Don't complain about the -nostdinc directrive */
			if (strcmp(optarg, "ostdinc")) {
				fprintf(stderr, "%s: Unknown option -%c%s\n",
					appname, ch, optarg);
				usage();
				/* NOTREACHED */
			}
			break;
		case 'o':
			if ((ofile = fopen(optarg, "w")) == NULL) {
				perror(optarg);
				stop(NULL, EX_CANTCREAT);
			}
			ofilename = optarg;
			break;
		case 'p':
			/* Create Register Diagnostic "printing" Functions */
			if ((regdiagfile = fopen(optarg, "w")) == NULL) {
				perror(optarg);
				stop(NULL, EX_CANTCREAT);
			}
			regdiagfilename = optarg;
			break;
		case 'r':
			if ((regfile = fopen(optarg, "w")) == NULL) {
				perror(optarg);
				stop(NULL, EX_CANTCREAT);
			}
			regfilename = optarg;
			break;
		case 'I':
		{
			path_entry_t include_dir;

			if (strcmp(optarg, "-") == 0) {
				if (includes_search_curdir == 0) {
					fprintf(stderr, "%s: Warning - '-I-' "
							"specified multiple "
							"times\n", appname);
				}
				includes_search_curdir = 0;
				for (include_dir = SLIST_FIRST(&search_path);
				     include_dir != NULL;
				     include_dir = SLIST_NEXT(include_dir,
							      links))
					/*
					 * All entries before a '-I-' only
					 * apply to includes specified with
					 * quotes instead of "<>".
					 */
					include_dir->quoted_includes_only = 1;
			} else {
				include_dir =
				    (path_entry_t)malloc(sizeof(*include_dir));
				if (include_dir == NULL) {
					perror(optarg);
					stop(NULL, EX_OSERR);
				}
				include_dir->directory = strdup(optarg);
				if (include_dir->directory == NULL) {
					perror(optarg);
					stop(NULL, EX_OSERR);
				}
				include_dir->quoted_includes_only = 0;
				SLIST_INSERT_HEAD(&search_path, include_dir,
						  links);
			}
			break;
		}
		case 'X':
			/* icc version of -nostdinc */
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (argc != 1) {
		fprintf(stderr, "%s: No input file specifiled\n", appname);
		usage();
		/* NOTREACHED */
	}

	if (regdiagfile != NULL
	 && (regfile == NULL || stock_include_file == NULL)) {
		fprintf(stderr,
			"%s: The -p option requires the -r and -i options.\n",
			appname);
		usage();
		/* NOTREACHED */
	}
	symtable_open();
	inputfilename = *argv;
	include_file(*argv, SOURCE_FILE);
	retval = yyparse();
	if (retval == 0) {
		if (SLIST_FIRST(&scope_stack) == NULL
		 || SLIST_FIRST(&scope_stack)->type != SCOPE_ROOT) {
			stop("Unterminated conditional expression", EX_DATAERR);
			/* NOTREACHED */
		}

		/* Process outmost scope */
		process_scope(SLIST_FIRST(&scope_stack));
		/*
		 * Decend the tree of scopes and insert/emit
		 * patches as appropriate.  We perform a depth first
		 * tranversal, recursively handling each scope.
		 */
		/* start at the root scope */
		dump_scope(SLIST_FIRST(&scope_stack));

		/* Patch up forward jump addresses */
		back_patch();

		if (ofile != NULL)
			output_code();
		if (regfile != NULL)
			symtable_dump(regfile, regdiagfile);
		if (listfile != NULL)
			output_listing(inputfilename);
	}

	stop(NULL, 0);
	/* NOTREACHED */
	return (0);
}