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
struct strip_args {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_default_allocf ; 
 int /*<<< orphan*/ * mrb_open_core (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int parse_args (int,char**,struct strip_args*) ; 
 int /*<<< orphan*/  print_usage (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strip (int /*<<< orphan*/ *,struct strip_args*) ; 

int
main(int argc, char **argv)
{
  struct strip_args args;
  int args_result;
  mrb_state *mrb;
  int ret;

  if (argc <= 1) {
    printf("no files to strip\n");
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  args_result = parse_args(argc, argv, &args);
  if (args_result < 0) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }
  mrb = mrb_open_core(mrb_default_allocf, NULL);
  if (mrb == NULL) {
    fputs("Invalid mrb_state, exiting mruby-strip\n", stderr);
    return EXIT_FAILURE;
  }

  ret = strip(mrb, &args);

  mrb_close(mrb);
  return ret;
}