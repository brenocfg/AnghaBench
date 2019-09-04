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
 int BROTLI_MAX_QUALITY ; 
 int BROTLI_MAX_WINDOW_BITS ; 
 int BROTLI_MIN_QUALITY ; 
 int BROTLI_MIN_WINDOW_BITS ; 
 int DEFAULT_LGWIN ; 
 char* DEFAULT_SUFFIX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void PrintHelp(const char* name) {
  /* String is cut to pieces with length less than 509, to conform C90 spec. */
  fprintf(stdout,
"Usage: %s [OPTION]... [FILE]...\n",
          name);
  fprintf(stdout,
"Options:\n"
"  -#                          compression level (0-9)\n"
"  -c, --stdout                write on standard output\n"
"  -d, --decompress            decompress\n"
"  -f, --force                 force output file overwrite\n"
"  -h, --help                  display this help and exit\n");
  fprintf(stdout,
"  -j, --rm                    remove source file(s)\n"
"  -k, --keep                  keep source file(s) (default)\n"
"  -n, --no-copy-stat          do not copy source file(s) attributes\n"
"  -o FILE, --output=FILE      output file (only if 1 input file)\n");
  fprintf(stdout,
"  -q NUM, --quality=NUM       compression level (%d-%d)\n",
          BROTLI_MIN_QUALITY, BROTLI_MAX_QUALITY);
  fprintf(stdout,
"  -t, --test                  test compressed file integrity\n"
"  -v, --verbose               verbose mode\n");
  fprintf(stdout,
"  -w NUM, --lgwin=NUM         set LZ77 window size (0, %d-%d) (default:%d)\n",
          BROTLI_MIN_WINDOW_BITS, BROTLI_MAX_WINDOW_BITS, DEFAULT_LGWIN);
  fprintf(stdout,
"                              window size = 2**NUM - 16\n"
"                              0 lets compressor choose the optimal value\n");
  fprintf(stdout,
"  -S SUF, --suffix=SUF        output file suffix (default:'%s')\n",
          DEFAULT_SUFFIX);
  fprintf(stdout,
"  -V, --version               display version and exit\n"
"  -Z, --best                  use best compression level (11) (default)\n"
"Simple options could be coalesced, i.e. '-9kf' is equivalent to '-9 -k -f'.\n"
"With no FILE, or when FILE is -, read standard input.\n"
"All arguments after '--' are treated as files.\n");
}