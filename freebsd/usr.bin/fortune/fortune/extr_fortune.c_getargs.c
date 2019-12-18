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
 void* All_forts ; 
 int Debug ; 
 void* Equal_probs ; 
 void* FALSE ; 
 void* Find_files ; 
 void* Long_only ; 
 void* Match ; 
 void* Offend ; 
 int /*<<< orphan*/  REG_BASIC ; 
 int /*<<< orphan*/  Re_pat ; 
 void* Short_only ; 
 void* TRUE ; 
 void* Wait ; 
 char* conv_pat (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  form_file_list (char**,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  print_file_list () ; 
 int regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
getargs(int argc, char *argv[])
{
	int	ignore_case;
	char	*pat;
	int ch;

	ignore_case = FALSE;
	pat = NULL;

#ifdef DEBUG
	while ((ch = getopt(argc, argv, "aDefilm:osw")) != -1)
#else
	while ((ch = getopt(argc, argv, "aefilm:osw")) != -1)
#endif /* DEBUG */
		switch(ch) {
		case 'a':		/* any fortune */
			All_forts = TRUE;
			break;
#ifdef DEBUG
		case 'D':
			Debug++;
			break;
#endif /* DEBUG */
		case 'e':		/* scatter un-allocted prob equally */
			Equal_probs = TRUE;
			break;
		case 'f':		/* find fortune files */
			Find_files = TRUE;
			break;
		case 'l':		/* long ones only */
			Long_only = TRUE;
			Short_only = FALSE;
			break;
		case 'o':		/* offensive ones only */
			Offend = TRUE;
			break;
		case 's':		/* short ones only */
			Short_only = TRUE;
			Long_only = FALSE;
			break;
		case 'w':		/* give time to read */
			Wait = TRUE;
			break;
		case 'm':			/* dump out the fortunes */
			Match = TRUE;
			pat = optarg;
			break;
		case 'i':			/* case-insensitive match */
			ignore_case++;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!form_file_list(argv, argc))
		exit(1);	/* errors printed through form_file_list() */
	if (Find_files) {
		print_file_list();
		exit(0);
	}
#ifdef DEBUG
	else if (Debug >= 1)
		print_file_list();
#endif /* DEBUG */

	if (pat != NULL) {
		int error;

		if (ignore_case)
			pat = conv_pat(pat);
		error = regcomp(&Re_pat, pat, REG_BASIC);
		if (error) {
			fprintf(stderr, "regcomp(%s) fails\n", pat);
			exit(1);
		}
	}
}