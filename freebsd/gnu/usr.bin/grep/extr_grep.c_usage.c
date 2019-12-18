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
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage (int status)
{
  if (status != 0)
    {
      fprintf (stderr, _("Usage: %s [OPTION]... PATTERN [FILE]...\n"),
	       program_name);
      fprintf (stderr, _("Try `%s --help' for more information.\n"),
	       program_name);
    }
  else
    {
      printf (_("Usage: %s [OPTION]... PATTERN [FILE] ...\n"), program_name);
      printf (_("\
Search for PATTERN in each FILE or standard input.\n\
Example: %s -i 'hello world' menu.h main.c\n\
\n\
Regexp selection and interpretation:\n"), program_name);
      printf (_("\
  -E, --extended-regexp     PATTERN is an extended regular expression\n\
  -F, --fixed-strings       PATTERN is a set of newline-separated strings\n\
  -G, --basic-regexp        PATTERN is a basic regular expression\n\
  -P, --perl-regexp         PATTERN is a Perl regular expression\n"));
      printf (_("\
  -e, --regexp=PATTERN      use PATTERN as a regular expression\n\
  -f, --file=FILE           obtain PATTERN from FILE\n\
  -i, --ignore-case         ignore case distinctions\n\
  -w, --word-regexp         force PATTERN to match only whole words\n\
  -x, --line-regexp         force PATTERN to match only whole lines\n\
  -z, --null-data           a data line ends in 0 byte, not newline\n"));
      printf (_("\
\n\
Miscellaneous:\n\
  -s, --no-messages         suppress error messages\n\
  -v, --invert-match        select non-matching lines\n\
  -V, --version             print version information and exit\n\
      --help                display this help and exit\n\
  -J, --bz2decompress       decompress bzip2'ed input before searching\n\
  -Z, --decompress          decompress input before searching (HAVE_LIBZ=1)\n\
      --mmap                use memory-mapped input if possible\n"));
      printf (_("\
\n\
Output control:\n\
  -m, --max-count=NUM       stop after NUM matches\n\
  -b, --byte-offset         print the byte offset with output lines\n\
  -n, --line-number         print line number with output lines\n\
      --line-buffered       flush output on every line\n\
  -H, --with-filename       print the filename for each match\n\
  -h, --no-filename         suppress the prefixing filename on output\n\
      --label=LABEL         print LABEL as filename for standard input\n\
  -o, --only-matching       show only the part of a line matching PATTERN\n\
  -q, --quiet, --silent     suppress all normal output\n\
      --binary-files=TYPE   assume that binary files are TYPE\n\
                            TYPE is 'binary', 'text', or 'without-match'\n\
  -a, --text                equivalent to --binary-files=text\n\
  -I                        equivalent to --binary-files=without-match\n\
  -d, --directories=ACTION  how to handle directories\n\
                            ACTION is 'read', 'recurse', or 'skip'\n\
  -D, --devices=ACTION      how to handle devices, FIFOs and sockets\n\
                            ACTION is 'read' or 'skip'\n\
  -R, -r, --recursive       equivalent to --directories=recurse\n\
      --include=PATTERN     files that match PATTERN will be examined\n\
      --exclude=PATTERN     files that match PATTERN will be skipped.\n\
      --exclude-from=FILE   files that match PATTERN in FILE will be skipped.\n\
  -L, --files-without-match only print FILE names containing no match\n\
  -l, --files-with-matches  only print FILE names containing matches\n\
  -c, --count               only print a count of matching lines per FILE\n\
      --null                print 0 byte after FILE name\n"));
      printf (_("\
\n\
Context control:\n\
  -B, --before-context=NUM  print NUM lines of leading context\n\
  -A, --after-context=NUM   print NUM lines of trailing context\n\
  -C, --context=NUM         print NUM lines of output context\n\
  -NUM                      same as --context=NUM\n\
      --color[=WHEN],\n\
      --colour[=WHEN]       use markers to distinguish the matching string\n\
                            WHEN may be `always', `never' or `auto'.\n\
  -U, --binary              do not strip CR characters at EOL (MSDOS)\n\
  -u, --unix-byte-offsets   report offsets as if CRs were not there (MSDOS)\n\
\n\
`egrep' means `grep -E'.  `fgrep' means `grep -F'.\n\
With no FILE, or when FILE is -, read standard input.  If less than\n\
two FILEs given, assume -h.  Exit status is 0 if match, 1 if no match,\n\
and 2 if trouble.\n"));
      printf (_("\nReport bugs to <bug-gnu-utils@gnu.org>.\n"));
    }
  exit (status);
}