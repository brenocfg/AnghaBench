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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* JQ_VERSION ; 
 int /*<<< orphan*/  exit (int) ; 
 int fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static void usage(int code, int keep_it_short) {
  FILE *f = stderr;

  if (code == 0)
    f = stdout;

  int ret = fprintf(f,
    "jq - commandline JSON processor [version %s]\n"
    "\nUsage:\t%s [options] <jq filter> [file...]\n"
    "\t%s [options] --args <jq filter> [strings...]\n"
    "\t%s [options] --jsonargs <jq filter> [JSON_TEXTS...]\n\n"
    "jq is a tool for processing JSON inputs, applying the given filter to\n"
    "its JSON text inputs and producing the filter's results as JSON on\n"
    "standard output.\n\n"
    "The simplest filter is ., which copies jq's input to its output\n"
    "unmodified (except for formatting, but note that IEEE754 is used\n"
    "for number representation internally, with all that that implies).\n\n"
    "For more advanced filters see the jq(1) manpage (\"man jq\")\n"
    "and/or https://stedolan.github.io/jq\n\n"
    "Example:\n\n\t$ echo '{\"foo\": 0}' | jq .\n"
    "\t{\n\t\t\"foo\": 0\n\t}\n\n",
    JQ_VERSION, progname, progname, progname);
  if (keep_it_short) {
    fprintf(f,
      "For a listing of options, use %s --help.\n",
      progname);
  } else {
    (void) fprintf(f,
      "Some of the options include:\n"
      "  -c               compact instead of pretty-printed output;\n"
      "  -n               use `null` as the single input value;\n"
      "  -e               set the exit status code based on the output;\n"
      "  -s               read (slurp) all inputs into an array; apply filter to it;\n"
      "  -r               output raw strings, not JSON texts;\n"
      "  -R               read raw strings, not JSON texts;\n"
      "  -C               colorize JSON;\n"
      "  -M               monochrome (don't colorize JSON);\n"
      "  -S               sort keys of objects on output;\n"
      "  --tab            use tabs for indentation;\n"
      "  --arg a v        set variable $a to value <v>;\n"
      "  --argjson a v    set variable $a to JSON value <v>;\n"
      "  --slurpfile a f  set variable $a to an array of JSON texts read from <f>;\n"
      "  --rawfile a f    set variable $a to a string consisting of the contents of <f>;\n"
      "  --args           remaining arguments are string arguments, not files;\n"
      "  --jsonargs       remaining arguments are JSON arguments, not files;\n"
      "  --               terminates argument processing;\n\n"
      "Named arguments are also available as $ARGS.named[], while\n"
      "positional arguments are available as $ARGS.positional[].\n"
      "\nSee the manpage for more options.\n");
  }
  exit((ret < 0 && code == 0) ? 2 : code);
}