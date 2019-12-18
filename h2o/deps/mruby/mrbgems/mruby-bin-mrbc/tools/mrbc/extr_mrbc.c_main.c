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
struct mrbc_args {char* prog; char* outfile; int idx; scalar_t__ check_syntax; scalar_t__ initname; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  C_EXT ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int MRB_DUMP_OK ; 
 int /*<<< orphan*/  RITEBIN_EXT ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ *,struct mrbc_args*) ; 
 int dump_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct mrbc_args*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 char* get_outfilename (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_file (int /*<<< orphan*/ *,struct mrbc_args*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mrb_open () ; 
 int /*<<< orphan*/  mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 int parse_args (int /*<<< orphan*/ *,int,char**,struct mrbc_args*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char **argv)
{
  mrb_state *mrb = mrb_open();
  int n, result;
  struct mrbc_args args;
  FILE *wfp;
  mrb_value load;

  if (mrb == NULL) {
    fputs("Invalid mrb_state, exiting mrbc\n", stderr);
    return EXIT_FAILURE;
  }

  n = parse_args(mrb, argc, argv, &args);
  if (n < 0) {
    cleanup(mrb, &args);
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  if (n == argc) {
    fprintf(stderr, "%s: no program file given\n", args.prog);
    return EXIT_FAILURE;
  }
  if (args.outfile == NULL && !args.check_syntax) {
    if (n + 1 == argc) {
      args.outfile = get_outfilename(mrb, argv[n], args.initname ? C_EXT : RITEBIN_EXT);
    }
    else {
      fprintf(stderr, "%s: output file should be specified to compile multiple files\n", args.prog);
      return EXIT_FAILURE;
    }
  }

  args.idx = n;
  load = load_file(mrb, &args);
  if (mrb_nil_p(load)) {
    cleanup(mrb, &args);
    return EXIT_FAILURE;
  }
  if (args.check_syntax) {
    printf("%s:%s:Syntax OK\n", args.prog, argv[n]);
  }

  if (args.check_syntax) {
    cleanup(mrb, &args);
    return EXIT_SUCCESS;
  }

  if (args.outfile) {
    if (strcmp("-", args.outfile) == 0) {
      wfp = stdout;
    }
    else if ((wfp = fopen(args.outfile, "wb")) == NULL) {
      fprintf(stderr, "%s: cannot open output file:(%s)\n", args.prog, args.outfile);
      return EXIT_FAILURE;
    }
  }
  else {
    fprintf(stderr, "Output file is required\n");
    return EXIT_FAILURE;
  }
  result = dump_file(mrb, wfp, args.outfile, mrb_proc_ptr(load), &args);
  fclose(wfp);
  cleanup(mrb, &args);
  if (result != MRB_DUMP_OK) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}